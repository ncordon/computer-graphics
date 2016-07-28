#include "escena.hpp"

EntradaNodo::EntradaNodo(Objeto3D *obj){
    objeto = obj;
    transformacion = NULL;
    es_transformacion = false;
}

EntradaNodo::EntradaNodo(const Matriz4f &mat){
    objeto = NULL;
    transformacion = new Matriz4f(mat);
    es_transformacion = true;
}
/*
EntradaNodo::~EntradaNodo(){
    if(objeto != NULL)
        delete objeto;
    if(transformacion != NULL)
        delete transformacion;
}*/

void NodoEscena::visualizar(unsigned modo){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    for (int i=0; i<escena.size(); ++i){
        if (escena.at(i).es_transformacion){
            glMultMatrixf ( *escena.at(i).transformacion);
        }
        else{
            // Visualizar el objeto
            escena.at(i).objeto-> visualizar(modo);
        }
    }

    glMatrixMode (GL_MODELVIEW);
    glPopMatrix();

}
