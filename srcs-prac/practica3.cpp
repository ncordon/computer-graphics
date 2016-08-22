#include "practica3.hpp"



// Grado de libertad actual seleccionado en el programa
int p3_grado_libertad_activo;
const int NUM_GRADOS_LIBERTAD = 3;
static NodoGrafoEscena *p3_obj;
static double   giro_offset,
                traslacion_offset,
                longitud_offset;
ContextoVis p3_cv;


void P3_Inicializar( int argc, char *argv[] ){
    p3_grado_libertad_activo = 1;
    giro_offset = 45;
    traslacion_offset = 1;
    longitud_offset = 1;
    p3_obj = new Grua(10,7,8,6,45);
}



bool P3_FGE_PulsarTeclaNormal(  unsigned char tecla ){
    bool tecla_correcta = false;

    switch(tecla){
    case 'G':
        p3_grado_libertad_activo %= NUM_GRADOS_LIBERTAD;
        p3_grado_libertad_activo += 1;

        break;
    case '>':
        tecla_correcta = true;
        //cerr << p3_grado_libertad_activo << endl;

        switch(p3_grado_libertad_activo){
        case 1:
            ((Grua*)p3_obj)->girarCabezaGrua(giro_offset);
            break;
        case 2:
            ((Grua*)p3_obj)->aumentarTraslacionGancho(traslacion_offset);
            break;
        case 3:
            ((Grua*)p3_obj)->aumentarLongitudGancho(longitud_offset);
            break;
        default:
            break;
        }
        // Aumentar grado de libertad

        // Si se sobrepasa el máximo, no redibujar
        break;
    case '<':
        tecla_correcta = true;

        switch(p3_grado_libertad_activo){
        case 1:
            ((Grua *)p3_obj)->girarCabezaGrua(-giro_offset);
            break;
        case 2:
            ((Grua*)p3_obj)->aumentarTraslacionGancho(-traslacion_offset);
            break;
        case 3:
            ((Grua*)p3_obj)->aumentarLongitudGancho(-longitud_offset);
            break;
        default:
            break;
        }

        break;

    default:
        tecla_correcta = false;
    }

    return tecla_correcta;
}

void P3_DibujarObjetos( unsigned modo ){
    p3_cv.modo_vis = modo;
    p3_obj->visualizar(p3_cv);
}
