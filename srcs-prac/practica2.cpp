// *********************************************************************
// **
// ** Informática Gráfica, curso 2015-16
// ** Práctica 2  (implementación)
// **
// *********************************************************************


#include "practica2.hpp"


unsigned p2_objeto_activo;
static MallaPLY * obj = NULL;
static MallaRevol * obj_rev = NULL;
const unsigned N_OBJETOS = 2;

void P2_Inicializar( int argc, char *argv[]){
    // Crear objeto de tipo malla PLY y objeto de revolución con new.

    if (argc != 4){
        cerr << "Número de argumentos incorrecto" << endl;
        cerr << "Uso: <nombre programa> <archivo PLY> <archivo PLY rev> <num copias perfil>" << endl;
        exit(1);
    }

    obj = new MallaPLY(argv[1]);
    obj_rev = new MallaRevol(argv[2], atoi(argv[3]));
    // Objeto 0 = ply, objeto 1 = revolución
    p2_objeto_activo = 0;
}


void P2_DibujarObjetos( unsigned modo ){
    if (p2_objeto_activo == 0)
         obj->visualizar (modo);
    else
         obj_rev->visualizar (modo);
}


bool P2_FGE_PulsarTeclaNormal(unsigned char tecla){
    bool tecla_correcta = false;

    if (tecla == 'O'){
        p2_objeto_activo += 1;
        p2_objeto_activo %= N_OBJETOS;
        tecla_correcta = true;
    }

    return tecla_correcta;
}
