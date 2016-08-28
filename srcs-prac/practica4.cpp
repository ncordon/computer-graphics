#include "practica4.hpp"


string p4_peon_file = "../plys/peon.ply";
string p4_lata_file = "./lata-pcue.ply";
string p4_lata_inf = "./lata-pinf.ply";
string p4_lata_sup = "./lata-psup.ply";
uint p4_resolucion_objs = 50;
ColeccionFL p4_fuentes;
int p4_angulo_actual;
static NodoGrafoEscena *p4_obj;
ContextoVis p4_cv;

Lata::Lata(){
    agregar(new MaterialTapasLata);
    agregar(new MallaRev(&p4_lata_inf[0], p4_resolucion_objs, false, false));
    agregar(new MallaRev(&p4_lata_sup[0], p4_resolucion_objs, false, false));
    agregar(new MaterialLata);
    agregar(new MallaRev(&p4_lata_file[0], p4_resolucion_objs, true, false));
}

PeonMadera::PeonMadera(){
    agregar(new MaterialPeonMadera);
    agregar(new MallaRev(&p4_peon_file[0], p4_resolucion_objs, true, true));
}


PeonBlanco::PeonBlanco(){
    agregar(new MaterialPeonBlanco);
    agregar(new MallaRev(&p4_peon_file[0], p4_resolucion_objs, true, true));
}


PeonNegro::PeonNegro(){
    agregar(new MaterialPeonNegro);
    agregar(new MallaRev(&p4_peon_file[0], p4_resolucion_objs, true, true));
}



void P4_Inicializar( int argc, char *argv[] ){
    p4_fuentes.fuentes.push_back(new FuenteDireccional(0,0));
    p4_fuentes.fuentes.push_back(new FuentePosicional(Tupla3f(-5,5,-5)));
    p4_fuentes.activar();

    p4_angulo_actual = 0;
    p4_resolucion_objs = 50;

    p4_obj = new NodoGrafoEscena;

    p4_obj->agregar(new Lata);
    p4_obj->agregar(MAT_Escalado(0.2,0.2,0.2));
    // Valor 1.4 tomado del peon.ply
    p4_obj->agregar(MAT_Traslacion(1,1.4,3));
    p4_obj->agregar(new PeonMadera);
    p4_obj->agregar(MAT_Traslacion(2.2,0,0));
    p4_obj->agregar(new PeonBlanco);
    p4_obj->agregar(MAT_Traslacion(2.2,0,0));
    p4_obj->agregar(new PeonNegro);
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
        ((FuenteDireccional*) p4_fuentes.fuentes[0])->variarAngulo( 0, p4_angulo_actual, 15.0 );
        break;
    case '<':
        tecla_correcta = true;
        ((FuenteDireccional*) p4_fuentes.fuentes[0])->variarAngulo( 0, p4_angulo_actual, -15.0 );
        break;
    default:
        tecla_correcta = false;
    }

    return tecla_correcta;
}


void P4_DibujarObjetos( unsigned modo ){
    p4_cv.modo_vis = modo;
    p4_obj->visualizar(p4_cv);
}
