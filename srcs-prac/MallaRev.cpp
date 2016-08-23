#include "MallaRev.hpp"

MallaRev::MallaRev( const char * nombre_arch, unsigned n_perfiles, bool con_textura ){
    std::vector<float> vertices_ply;

    ply::read_vertices(nombre_arch, vertices_ply);

    int n_vertices = vertices_ply.size()/3;
    double  seno,
            coseno,
            angulo;


    for (int j=0; j <= n_perfiles; ++j){
        for (int i=0; i < n_vertices; ++i){
            angulo = 2*PI*j/n_perfiles;
            // Asumimos el último valor para cada vértice nulo
            coseno = cos(angulo);
            seno = sin(angulo);

            vertices.push_back(Tupla3f(
                coseno * vertices_ply[i*3] - seno * vertices_ply[i*3+2],
                vertices_ply[i*3+1],
                seno * vertices_ply [i*3] + coseno * vertices_ply[i*3+2]
            ));

            if(i!=0 && j!=n_perfiles){
                caras.push_back(Tupla3i(
                    j*n_vertices + i,
                    (j+1) * n_vertices + i,
                    j*n_vertices + i -1
                ));

                caras.push_back(Tupla3i( j*n_vertices + i-1,
                    (j+1) * n_vertices + i,
                    (j+1) * n_vertices + i-1
                ));
            }
        }
    }


    // Ejes superior e inferior
    vertices.push_back(Tupla3f(0.0, vertices_ply[1], 0.0));
    vertices.push_back(Tupla3f(0.0, vertices_ply[n_vertices*3-2], 0.0));

    int upper_vertex = vertices.size()-1;
    int lower_vertex = vertices.size()-2;



    // Metemos las tapas superior e inferior
    for (int j=0; j < n_perfiles; ++j){
        caras.push_back(Tupla3i(
            (j+1)*n_vertices-1,
            upper_vertex,
            (j+2)*n_vertices - 1
        ));
    }

    for (int j=0; j < n_perfiles; ++j){
        caras.push_back(Tupla3i(
            j * n_vertices,
            (j+1) * n_vertices,
            lower_vertex
        ));
    }


    // Calculamos las coordenadas de textura
    if (con_textura)
        calcularTexturas(n_perfiles, n_vertices);

    calcularNormales();
}

void MallaRev::calcularTexturas(unsigned n_perfiles, unsigned n_vertices){
    double distancias[n_vertices];

    // Calculamos el vector de "distancias" entre los puntos de los perfiles
    distancias[0] = 0;

    for (int i=1; i < n_vertices; i++)
        distancias[i] = distancias[i-1] +
                        sqrt( (vertices[i] - vertices[i-1]).dot(vertices[i] - vertices[i-1]) );

    for (int i=1; i < n_vertices; i++)
        distancias[i] = distancias[i]/distancias[n_vertices - 1];


    for (int j=0; j <= n_perfiles; ++j){
        for (int i=0; i < n_vertices; ++i){
            textura_coords.push_back(Tupla2f((j*1.0)/n_perfiles, distancias[i]));
        }
    }
}
