#include "MallaPLY.hpp"


MallaPLY::MallaPLY( const char * nombre_arch ){
    std::vector<float> vertices_ply;
    std::vector<int> caras_ply;

    ply::read(nombre_arch, vertices_ply, caras_ply);

    for (int i=0; i < vertices_ply.size()/3; ++i){
        vertices.push_back(Tupla3f( vertices_ply[i*3],
                                    vertices_ply[i*3+1],
                                    vertices_ply[i*3+2] ) );
    }

    for (int i=0; i < caras_ply.size()/3; ++i){
        caras.push_back(Tupla3i( caras_ply[i*3],
                                 caras_ply[i*3+1],
                                 caras_ply[i*3+2] ) );
    }
}
