#include "practica4.hpp"


string p4_peon_file = "../plys/peon.ply";
uint p4_resolucion_peon;
ColeccionFL p4_fuentes;
int p4_angulo_actual;


PeonMadera::PeonMadera(){
    agregar(new MallaRev(&p4_peon_file[0], p4_resolucion_peon, true));
}


PeonBlanco::PeonBlanco(){
    agregar(new MallaRev(&p4_peon_file[0], p4_resolucion_peon, true));
}


PeonNegro::PeonNegro(){
    agregar(new MallaRev(&p4_peon_file[0], p4_resolucion_peon, true));
}



void P4_Inicializar( int argc, char *argv[] ){
    p4_fuentes.fuentes.push_back(new FuenteDireccional(0,0));
    p4_fuentes.fuentes.push_back(new FuentePosicional(Tupla3f(0,0,0)));
    p4_angulo_actual = 0;
    p4_resolucion_peon = 50;
}



bool P4_FGE_PulsarTeclaNormal(  unsigned char tecla ){
    bool tecla_correcta = false;

    switch(tecla){
    case 'G':
        // Conmutamos entre alpha y beta
        p4_angulo_actual += 1;
        p4_angulo_actual %= 2;
        break;
    case '>':
        tecla_correcta = true;
        ((FuenteDireccional*) p4_fuentes.fuentes[0])->variarAngulo( 0, p4_angulo_actual, 1.0 );
        break;
    case '<':
        tecla_correcta = true;
        ((FuenteDireccional*) p4_fuentes.fuentes[0])->variarAngulo( 0, p4_angulo_actual, -1.0 );
        break;
    default:
        tecla_correcta = false;
    }

    return tecla_correcta;
}

bool P4_FGE_TeclaNormal( int tecla, int x_raton, int y_raton ){
    bool tecla_correcta = false;

    /*
    switch(tecla){
    case 'G':
        break;
    case '<':
        tecla_correcta = true;
        break;

    default:
        tecla_correcta = false;
    }
    */

    return tecla_correcta;
}

bool P4_FGE_TeclaEspecial( int tecla, int x_raton, int y_raton ){
    bool tecla_correcta = false;

    /*
    switch(tecla){
    case 'G':
        break;
    case '<':
        tecla_correcta = true;
        break;

    default:
        tecla_correcta = false;
    }
    */

    return tecla_correcta;
}


void P4_DibujarObjetos( unsigned modo ){
    //p3_obj->visualizar(modo);
}
