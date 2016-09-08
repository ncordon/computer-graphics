#include "escena.hpp"

void NodoGrafoEscena::visualizar(ContextoVis &cv){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    Material * materialActivoInicial = cv.materialActivo;

    for (int i=0; i<entradas.size(); ++i){
        if (entradas.at(i).esTransformacion()){
            glMultMatrixf ( *entradas.at(i).transformacion);
        }
        else if (entradas.at(i).esObjeto()){
            // Visualizar el objeto
            entradas.at(i).objeto-> visualizar(cv);
        }
        // Es una textura
        else if (entradas.at(i).material != cv.materialActivo){
            cv.materialActivo = entradas[i].material;
            entradas[i].material -> activar();
        }
    }

    // Restauramos el material inicial
    if (materialActivoInicial != cv.materialActivo){
        cv.materialActivo = materialActivoInicial;
        if (cv.materialActivo != NULL)
            cv.materialActivo->activar();
    }
    glMatrixMode (GL_MODELVIEW);
    glPopMatrix();

}


NodoGrafoEscena* NodoGrafoEscena::buscarNodoConIdent(unsigned char identBuscado){
    NodoGrafoEscena* result = NULL;

    if( identBuscado!= 0 ){
        if (this->identificador == identBuscado)
            result = this;

        for (int i = 0; i < entradas.size() && (result!=NULL); i++){
            if(entradas[i].esNodo())
                result = ((NodoGrafoEscena*) (entradas[i].objeto))->buscarNodoConIdent(identBuscado);
        }
    }
    return result;
}

void NodoGrafoEscena::modoSeleccion(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glColor3ub(identificador,0,0);

    for (int i=0; i<entradas.size(); ++i){
        if (entradas.at(i).esTransformacion()){
            glMultMatrixf ( *entradas.at(i).transformacion);
        }
        else if (entradas.at(i).esObjeto()){
            // Visualizar el objeto
            if(entradas.at(i).esNodo()){
                cerr << entradas.at(i).objeto->nombre() << endl;
                cerr << " " << (int) (((NodoGrafoEscena*)entradas.at(i).objeto)) -> identificador << endl;
                ((NodoGrafoEscena*)entradas.at(i).objeto) -> modoSeleccion();
            }
        }
    }

    glMatrixMode (GL_MODELVIEW);
    glPopMatrix();
}
