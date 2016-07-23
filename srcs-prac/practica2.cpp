// *********************************************************************
// **
// ** Informática Gráfica, curso 2015-16
// ** Práctica 2  (implementación)
// **
// *********************************************************************


#include "practica2.hpp"


unsigned p2_objeto_activo;
static MallaPLY* obj_ply = NULL;
static MallaRev* obj_rev = NULL;
static MallaBarrido* obj_barrido = NULL;
const unsigned N_OBJETOS = 3;

void P2_Inicializar( int argc, char *argv[]){
    // Crear objeto de tipo malla PLY y objeto de revolución con new.
    string  archivo_ply,
            archivo_rev,
            archivo_barrido;
    unsigned n_perfiles;
    Tupla3f dir;

    if (argc > 1 && argc < 8){
        cerr << "Número de argumentos incorrecto" << endl;
        cerr << "Uso: <nombre programa> <archivo PLY> <archivo PLY rev> <num perfiles revolucion>"
             << "<archivo PLY barrido> <vector barrido separado por espacios> " << endl;
        exit(1);
    }
    else if(argc == 8){
        archivo_ply = argv[1];
        archivo_rev = argv[2];
        archivo_barrido = argv[4];
        n_perfiles = atoi(argv[3]);
        dir = Tupla3f(atof(argv[5]), atof(argv[6]), atof(argv[7]));
    }
    // Parámetros por defecto para que pueda usarse directamente desde el make
    else{
        archivo_ply = "../plys/ant.ply";
        archivo_rev = "../plys/peon.ply";
        archivo_barrido = "../plys/peon.ply";
        n_perfiles = 20;
        dir = Tupla3f(1,0,0);
    }

    obj_ply = new MallaPLY(&archivo_ply[0]);
    obj_rev = new MallaRev(&archivo_rev[0], n_perfiles);
    obj_barrido = new MallaBarrido(&archivo_barrido[0], dir);
    // Objeto 0 = ply, objeto 1 = revolución
    p2_objeto_activo = 0;
}


void P2_DibujarObjetos( unsigned modo ){
    if (p2_objeto_activo == 0)
         obj_ply -> visualizar(modo);
    else if(p2_objeto_activo == 1)
         obj_rev -> visualizar(modo);
    else
        obj_barrido -> visualizar(modo);
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
