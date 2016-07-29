#include "grua.hpp"

Viga::Viga(double longitud){
    agregar(MAT_Escalado(0.05,longitud,0.05));
    agregar(new Cilindro);
}


VigaDiagonal::VigaDiagonal(double longitud){
    agregar(MAT_Traslacion(1,0,0));
    agregar(MAT_Escalado(-1,1,1));
    agregar(MAT_Rotacion(-45,0,0,1));
    agregar(new Viga(longitud));
}


ParColumnas::ParColumnas(){
    agregar(new Viga);
    agregar(MAT_Traslacion(1,0,0));
    agregar(new Viga);
}


ArmazonBasico::ArmazonBasico(){
    agregar(new VigaDiagonal(sqrt(2)));
    agregar(new ParColumnas);
    agregar(MAT_Traslacion(1,0,0));
    agregar(MAT_Rotacion(90,0,0,1));
    agregar(new ParColumnas);
}


ParArmazon::ParArmazon(){
    agregar(new ArmazonBasico);
    agregar(MAT_Traslacion(1,0,1));
    agregar(MAT_Escalado(-1,1,1));
    agregar(new ArmazonBasico);
}



TiraTriangulada::TiraTriangulada(unsigned num_cubos){
    agregar(new ArmazonBasico);

    for(int i=0; i<num_cubos-1; i++){
        agregar(MAT_Traslacion(0,1,0));
        agregar(new ArmazonBasico);
    }
}

ParTiraTriangulada::ParTiraTriangulada(unsigned num_cubos){
    agregar(new TiraTriangulada(num_cubos));
    agregar(MAT_Traslacion(1,0,1));
    agregar(MAT_Rotacion(180,0,1,0));
    agregar(new TiraTriangulada(num_cubos));
}

BrazoVertical::BrazoVertical(unsigned num_cubos){
    agregar(new ParTiraTriangulada(num_cubos));
    agregar(MAT_Traslacion(0,0,1));
    agregar(MAT_Rotacion(90,0,1,0));
    agregar(new ParTiraTriangulada(num_cubos));
}

LateralBrazoHorizontal::LateralBrazoHorizontal(unsigned num_cubos){
    agregar(new TiraTriangulada(num_cubos));
    agregar(MAT_Traslacion(0,-1,0));
    agregar(new VigaDiagonal(sqrt(2)));
    agregar(MAT_Traslacion(1,0,0));
    agregar(new Viga);
}

BrazoHorizontal::BrazoHorizontal(unsigned num_cubos){
    NodoEscena *un_lateral = new NodoEscena;
    NodoEscena *otro_lateral = new NodoEscena;
    NodoEscena *tapa = new NodoEscena;
    un_lateral->agregar(MAT_Rotacion(-30,0,1,0));
    un_lateral->agregar(new LateralBrazoHorizontal(num_cubos));
    otro_lateral->agregar(MAT_Rotacion(30,0,1,0));
    otro_lateral->agregar(new LateralBrazoHorizontal(num_cubos));
    tapa->agregar(MAT_Traslacion(sqrt(1-0.5*0.5),-1,0.5));
    tapa->agregar(MAT_Rotacion(90,0,1,0));
    tapa->agregar(new TiraTriangulada(num_cubos+1));

    agregar(MAT_Traslacion(-1.0*num_cubos,0,0.5));
    agregar(MAT_Rotacion(-90,0,0,1));
    agregar(un_lateral);
    agregar(otro_lateral);
    agregar(tapa);
}

TrianguloRemate::TrianguloRemate(){
    NodoEscena *viga_diag = new NodoEscena;
    double alpha = 90 - atan(2/0.5)/PI*180;

    viga_diag->agregar(MAT_Rotacion(-alpha,0,0,1));
    viga_diag->agregar(new Viga(sqrt(5)-0.2));
    agregar(MAT_Rotacion(alpha,1,0,0));
    agregar(viga_diag);
    // El 1.1 me permite corregir la anchura de la barra
    agregar(MAT_Traslacion(1,0,0));
    agregar(MAT_Escalado(-1,1,1));
    agregar(viga_diag);
}

RemateBrazoHorizontal::RemateBrazoHorizontal(){
    agregar(new TrianguloRemate);
    agregar(MAT_Traslacion(0,0,1));
    agregar(MAT_Escalado(1,1,-1));
    agregar(new TrianguloRemate);
}


ContrapesoBrazoHorizontal::ContrapesoBrazoHorizontal(unsigned longitud){
    NodoEscena *contrapeso = new NodoEscena;

    contrapeso->agregar(MAT_Escalado(2,-1,1));
    contrapeso->agregar(new Cubo);

    agregar(MAT_Traslacion(longitud+1,0,0));
    agregar(MAT_Escalado(-1,1,1));
    agregar(contrapeso);
    agregar(MAT_Escalado(longitud,0.1,1));
    agregar(new Cubo);
}

BaseGrua::BaseGrua(){
    agregar(MAT_Traslacion(-0.25,0,-0.25));
    agregar(MAT_Escalado(1.5,0.5,1.5));
    agregar(new Cubo);
}
