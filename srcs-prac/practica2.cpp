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
    string  archivo_ply,
            archivo_rev;
    unsigned n_perfiles;

    if (argc > 1 && argc < 4){
        cerr << "Número de argumentos incorrecto" << endl;
        cerr << "Uso: <nombre programa> <archivo PLY> <archivo PLY rev> <num copias perfil>" << endl;
        exit(1);
    }
    else if(argc == 4){
        archivo_ply = argv[1];
        archivo_rev = argv[2];
        n_perfiles = atoi(argv[3]);
    }
    // Parámetros por defecto para que pueda usarse directamente desde el make
    else{
        archivo_ply = "../plys/ant.ply";
        archivo_rev = "../plys/peon.ply";
        n_perfiles = 20;
    }

    obj = new MallaPLY(&archivo_ply[0]);
    obj_rev = new MallaRevol(&archivo_rev[0], n_perfiles);
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
