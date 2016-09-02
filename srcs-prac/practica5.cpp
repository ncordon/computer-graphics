#include "practica5.hpp"


string p5_peon_file = "../plys/peon.ply";
string p5_lata_file = "./lata-pcue.ply";
string p5_lata_inf = "./lata-pinf.ply";
string p5_lata_sup = "./lata-psup.ply";
uint p5_resolucion_objs = 50;
ColeccionFL p5_fuentes;
int p5_angulo_actual;
static NodoGrafoEscena *p5_obj;
ContextoVis p5_cv;

Lata::Lata(){
    agregar(new MaterialTapasLata);
    agregar(new MallaRev(&p5_lata_inf[0], p5_resolucion_objs, false, false));
    agregar(new MallaRev(&p5_lata_sup[0], p5_resolucion_objs, false, false));
    agregar(new MaterialLata);
    agregar(new MallaRev(&p5_lata_file[0], p5_resolucion_objs, true, false));
}

PeonMadera::PeonMadera(){
    agregar(new MaterialPeonMadera);
    agregar(new MallaRev(&p5_peon_file[0], p5_resolucion_objs, true, true));
}


PeonBlanco::PeonBlanco(){
    agregar(new MaterialPeonBlanco);
    agregar(new MallaRev(&p5_peon_file[0], p5_resolucion_objs, true, true));
}


PeonNegro::PeonNegro(){
    agregar(new MaterialPeonNegro);
    agregar(new MallaRev(&p5_peon_file[0], p5_resolucion_objs, true, true));
}



void P5_Inicializar( int argc, char *argv[] ){
    p5_fuentes.fuentes.push_back(new FuenteDireccional(-10,0));
    p5_fuentes.fuentes.push_back(new FuentePosicional(Tupla3f(0,5,5)));
    p5_fuentes.activar();

    p5_angulo_actual = 0;
    p5_resolucion_objs = 50;

    p5_obj = new NodoGrafoEscena;

    p5_obj->agregar(new Lata);
    p5_obj->agregar(MAT_Escalado(0.2,0.2,0.2));
    // Valor 1.4 tomado del peon.ply
    p5_obj->agregar(MAT_Traslacion(1,1.4,3));
    p5_obj->agregar(new PeonMadera);
    p5_obj->agregar(MAT_Traslacion(2.2,0,0));
    p5_obj->agregar(new PeonBlanco);
    p5_obj->agregar(MAT_Traslacion(2.2,0,0));
    p5_obj->agregar(new PeonNegro);
}



bool P5_FGE_PulsarTeclaNormal(  unsigned char tecla ){
    bool tecla_correcta = false;

    switch(tecla){
    case 'G':
        // Conmutamos entre alpha y beta
        p5_angulo_actual += 1;
        p5_angulo_actual %= 2;
        break;
    case '>':
        tecla_correcta = true;
        ((FuenteDireccional*) p5_fuentes.fuentes[0])->variarAngulo( 0, p5_angulo_actual, 15.0 );
        break;
    case '<':
        tecla_correcta = true;
        ((FuenteDireccional*) p5_fuentes.fuentes[0])->variarAngulo( 0, p5_angulo_actual, -15.0 );
        break;
    default:
        tecla_correcta = false;
    }

    return tecla_correcta;
}


void P5_DibujarObjetos( unsigned modo ){
    p5_cv.modo_vis = modo;
    p5_obj->visualizar(p5_cv);
}

void P5_FijarMVPOpenGL(){

}
