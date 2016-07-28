#include "grua.hpp"

Viga::Viga(double longitud){
    agregar(MAT_Escalado(0.05,longitud,0.05));
    agregar(new Cilindro);
}


ParColumnas::ParColumnas(){
    agregar(new Viga);
    agregar(MAT_Traslacion(1,0,0));
    agregar(new Viga);
}


ArmazonBasico::ArmazonBasico(){
    NodoEscena *viga_diagonal = new NodoEscena;
    viga_diagonal->agregar(MAT_Traslacion(1,0,0));
    viga_diagonal->agregar(MAT_Rotacion(45,0,0,1));
    viga_diagonal->agregar(new Viga(sqrt(2)));

    agregar(new ParColumnas);
    agregar(MAT_Traslacion(1,0,0));
    agregar(MAT_Rotacion(90,0,0,1));
    agregar(new ParColumnas);
    agregar(viga_diagonal);
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

BrazoHorizontal::BrazoHorizontal(unsigned num_cubos){
    unsigned num_cubos_horizontal = (int)(num_cubos*5.0/6);
    NodoEscena *un_lateral = new NodoEscena;
    NodoEscena *otro_lateral = new NodoEscena;
    NodoEscena *tapa = new NodoEscena;
    un_lateral->agregar(MAT_Rotacion(-30,0,1,0));
    un_lateral->agregar(new TiraTriangulada(num_cubos_horizontal));
    otro_lateral->agregar(MAT_Rotacion(30,0,1,0));
    otro_lateral->agregar(new TiraTriangulada(num_cubos_horizontal));
    tapa->agregar(MAT_Traslacion(sqrt(1-0.5*0.5),0,0.5));
    tapa->agregar(MAT_Rotacion(90,0,1,0));
    tapa->agregar(new TiraTriangulada(num_cubos_horizontal));


    agregar(MAT_Traslacion(-1.0*num_cubos_horizontal, num_cubos+sqrt(1-0.5*0.5),0.5));
    agregar(MAT_Rotacion(-90,0,0,1));
    agregar(un_lateral);
    agregar(otro_lateral);
    agregar(tapa);
}
