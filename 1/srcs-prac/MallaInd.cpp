#include "MallaInd.hpp"

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
