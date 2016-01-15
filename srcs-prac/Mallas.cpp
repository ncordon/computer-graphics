#include "Mallas.hpp"


void MallaInd::visualizar(unsigned modo_vis){
    if (modo_vis < 3){
        glColor3f(0.2, 0.2, 0.2);
        
        switch(modo_vis){
        case(0):
            // Modo puntos
            glPolygonMode (GL_FRONT_AND_BACK, GL_POINT);
            break;
        case(1):
            // Modo alambre
            glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
            break;
        case(2):
            // Modo sólido
            glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
            break;
        }
        
        
        for (unsigned int i=0; i < caras.size(); ++i){
            glBegin ( GL_TRIANGLES );
        
            for (unsigned int j=0; j < 3; ++j){
                glVertex3fv ( (float *) vertices[caras[i](j)] );
            }
        
            glEnd();
        }
    }
    // Modo ajedrez
    else{
        glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);

        // Dibuja las caras pares en un color
        glColor3f(0.2, 0.2, 0.2);
        for (unsigned int i=0; i < caras.size(); i+=2){
            glBegin ( GL_TRIANGLES );
        
            for (unsigned int j=0; j < 3; ++j){
                glVertex3fv ( (float *) vertices[caras[i](j)] );
            }
        
            glEnd();
        }

        // Dibuja las caras impares en otro color
        glColor3f(0.8, 0.8, 0.8);
        for (unsigned int i=1; i < caras.size(); i+=2){
            glBegin ( GL_TRIANGLES );
        
            for (unsigned int j=0; j < 3; ++j){
                glVertex3fv ( (float *) vertices[caras[i](j)] );
            }
        
            glEnd();
        }
    }
}

MallaPLY::MallaPLY( const char * nombre_arch ){
    vector<float> vertices_ply;
    vector<int> caras_ply;
       
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

MallaRevol::MallaRevol( const char * nombre_arch, unsigned n_perfiles ){
    vector<float> vertices_ply;
           
    ply::read_vertices(nombre_arch, vertices_ply);

    int n_vertices = vertices_ply.size()/3;
    double seno;
    double coseno;
    
    for (int j=0; j < n_perfiles; ++j){
        for (int i=0; i < n_vertices; ++i){
            // Asumimos el último valor para cada vértice nulo
            coseno = cos(2*PI*j/n_perfiles);
            seno = sin(2*PI*j/n_perfiles);
            
            vertices.push_back(Tupla3f( coseno * vertices_ply [i*3] + seno * vertices_ply [i*3+2],
                                        vertices_ply[i*3+1],
                                        -seno * vertices_ply [i*3] + coseno * vertices_ply [i*3+2]
                                        ) );
            if (i!=0){    
                caras.push_back(Tupla3i( j*n_vertices + i,
                                         ( (j+1) % n_perfiles) * n_vertices + i,
                                         j*n_vertices + i -1
                                         ));
                caras.push_back(Tupla3i( j*n_vertices + i -1,
                                         ( (j+1) % n_perfiles) * n_vertices + i,
                                         ((j+1) % n_perfiles) * n_vertices + i -1
                                         ));
                                

            }
            
        }
    }
    // Metemos la tapa inferior y superior
    vertices.push_back(Tupla3f(0.0, vertices_ply[1], 0.0));
    vertices.push_back(Tupla3f(0.0, vertices_ply[(n_vertices-1)*3+1], 0.0));

    for (int j=0; j < n_perfiles; ++j){
        caras.push_back(Tupla3i( j * n_vertices,
                                 ( (j+1) % n_perfiles) * n_vertices,
                                 n_vertices+1));
        caras.push_back(Tupla3i( (j+1) * n_vertices-1,
                                 n_vertices+2,
                                 ( (j+2) % n_perfiles )*n_vertices - 1
                                 ));
    }
                                
}
