#include "MallaBarrido.hpp"

MallaBarrido::MallaBarrido( const char * nombre_arch, Tupla3f dir_volumen){
    std::vector<float> vertices_ply;

    ply::read_vertices(nombre_arch, vertices_ply);

    int n_vertices = vertices_ply.size()/3;


    for (int i=0; i < n_vertices; ++i)
        vertices.push_back(Tupla3f(vertices_ply[3*i], vertices_ply[3*i+1], vertices_ply[3*i+2]));

    for (int i=0; i < n_vertices; ++i){
        //std::cout << "Vértices[i]: " << vertices[i] << std::endl;
        //std::cout << "Vértice desplazado: " << (vertices[i] + dir_volumen) << std::endl;
        vertices.push_back(vertices[i] + dir_volumen);

        if(i!=0){
            caras.push_back(Tupla3i(i-1, i-1+n_vertices, i+n_vertices));
            caras.push_back(Tupla3i(i, i-1, i+n_vertices));
        }
    }
}
