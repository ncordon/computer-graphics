#include "escena.hpp"

void NodoEscena::visualizar(unsigned modo){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    for (int i=0; i<entradas.size(); ++i){
        if (entradas.at(i).es_transformacion){
            glMultMatrixf ( *entradas.at(i).transformacion);
        }
        else{
            // Visualizar el objeto
            entradas[i].objeto-> visualizar(modo);
        }
    }

    glMatrixMode (GL_MODELVIEW);
    glPopMatrix();

}
