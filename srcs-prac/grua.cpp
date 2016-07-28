#include "grua.hpp"

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

Viga::Viga(double longitud){
    agregar(MAT_Escalado(0.05,longitud,0.05));
    agregar(new Cilindro);
}
