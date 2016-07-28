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
    agregar(new ParColumnas);
    agregar(MAT_Traslacion(0.5,-0.5,0));
    agregar(MAT_Rotacion(90,0,0,1));
    agregar(new ParColumnas);
    agregar(MAT_Traslacion(0.5,0,0));
    agregar(MAT_Rotacion(45,0,0,1));
    agregar(new Viga(sqrt(2)));
}


ParArmazon::ParArmazon(){
    agregar(new ArmazonBasico);
    agregar(MAT_Traslacion(1,0,1));
    agregar(MAT_Escalado(-1,1,1));
    agregar(new ArmazonBasico);
}


CuboBasico::CuboBasico(){
    agregar(new ParArmazon);
    agregar(MAT_Traslacion(0,0,1));
    agregar(MAT_Rotacion(90,0,1,0));
    agregar(new ParArmazon);
}

CuboTriangulado::CuboTriangulado(){
    agregar(new CuboBasico);
    agregar(MAT_Traslacion(0,0.5,0.5));
    agregar(MAT_Rotacion(90,1,0,0));
    agregar(new ParArmazon);
}

BrazoGrua::BrazoGrua(unsigned num_cubos){
    agregar(new CuboTriangulado);

    for(int i=0; i<num_cubos-1; i++){
        agregar(MAT_Traslacion(0,1,0));
        agregar(new CuboTriangulado);
    }
}
