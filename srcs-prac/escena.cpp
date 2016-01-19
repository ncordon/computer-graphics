#include "escena.hpp"

EntradaNodo::EntradaNodo( Objeto3D * obj){
    objeto = obj;
    matriz = NULL;
    es_transformacion = false;
}

EntradaNodo::EntradaNodo ( Matriz4f * mat){
    objeto = NULL;
    matriz = mat;
    es_transformacion = true;
}

EntradaNodo::~EntradaNodo(){
    if(objeto != NULL)
        delete objeto;
    if(matriz != NULL)
        delete matriz;
}

void NodoEscena::visualizar(){
    glMatrixMode ( GL_MODELVIEW );
    glPushMatrix();
    
    for (int i=0; i< escena.size; ++i){
        if (escena.at(i).es_transformacion){
            glMultMatrixf ( *escena.at(i).matriz);
        }
        else{
            // Visualizar el objeto
            escena.at(i).objeto-> visualizar();
        }
    }

    glMatrixMode ( GL_MODELVIEW );
    glPopMatrix();
    
}
