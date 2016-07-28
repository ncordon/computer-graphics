#include "practica3.hpp"



// Grado de libertad actual seleccionado en el programa
int p3_grado_libertad_activo;
const int NUM_GRADOS_LIBERTAD = 3;
static NodoEscena *p3_obj;


void P3_Inicializar( int argc, char *argv[] ){
    p3_grado_libertad_activo = 0;
    p3_obj = new Grua;
}



bool P3_FGE_PulsarTeclaNormal(  unsigned char tecla ){
    bool tecla_correcta = false;

    switch(tecla){
    case 'G':
        p3_grado_libertad_activo += 1;
        p3_grado_libertad_activo %= NUM_GRADOS_LIBERTAD;

        break;
    case '>':
        // Aumentar grado de libertad

        // Si se sobrepasa el máximo, no redibujar
        break;
    case '<':

        break;

    default:
        tecla_correcta = false;
    }

    return tecla_correcta;
}

void P3_DibujarObjetos( unsigned modo ){
    p3_obj->visualizar(modo);
}
