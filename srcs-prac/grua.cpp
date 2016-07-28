#include "grua.hpp"

ArmazonBasico::ArmazonBasico(){
    agregar(new Viga);
    agregar(MAT_Traslacion(0,1,0));
    agregar(MAT_Rotacion(-PI/2.0, 0,0,1));
    agregar(new Viga);
    agregar(MAT_Traslacion(1,0,0));
    agregar(MAT_Rotacion(-PI/2.0, 0,0,1));
    agregar(new Viga);
    agregar(MAT_Traslacion(0,-1,0));
    agregar(MAT_Rotacion(-PI/2.0, 0,0,1));
    agregar(new Viga);
    agregar(MAT_Traslacion(-1,0,0));
    agregar(MAT_Rotacion(-PI/2.0 ,0,0,1));
    agregar(new Viga);
    agregar(MAT_Rotacion(-PI/4.0, 0,0,1));
    agregar(new Viga);
}

Viga::Viga(){
    agregar(MAT_Escalado(0.2,1,1));
    agregar(new Cilindro);
}
