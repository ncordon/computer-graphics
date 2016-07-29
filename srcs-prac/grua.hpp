#include "practica1.hpp"
#include "practica2.hpp"
#include "escena.hpp"
#include <iostream>
#include <cctype>

#ifndef _GRUA_H_
#define _GRUA_H_


class Viga : public NodoEscena{
public:
    Viga(double longitud = 1.0);
};


class VigaDiagonal : public NodoEscena{
public:
    VigaDiagonal(double longitud = 1.0);
};


class ParColumnas : public NodoEscena{
public:
    ParColumnas();
};


class ArmazonBasico : public NodoEscena{
public:
    ArmazonBasico();
};


class ParArmazon : public NodoEscena{
public:
    ParArmazon();
};


class TiraTriangulada : public NodoEscena{
public:
    TiraTriangulada(unsigned num_cubos);
};


class ParTiraTriangulada : public NodoEscena{
public:
    ParTiraTriangulada(unsigned num_cubos);
};


class BrazoVertical: public NodoEscena{
public:
    BrazoVertical(unsigned num_cubos);
};


class LateralBrazoHorizontal: public NodoEscena{
public:
    LateralBrazoHorizontal(unsigned num_cubos);
};


class BrazoHorizontal: public NodoEscena{
public:
    BrazoHorizontal(unsigned num_cubos);
};


class RemateBrazoHorizontal : public NodoEscena{
public:
    RemateBrazoHorizontal(unsigned num_cubos);
};

class BaseGrua : public NodoEscena{
public:
    BaseGrua();
};

class Grua : public NodoEscena{
public:
    Grua(){
        unsigned num_cubos_vertical = 10;
        unsigned num_cubos_horizontal = (int)(num_cubos_vertical*5.0/6);
        agregar(new BaseGrua);
        agregar(MAT_Traslacion(0,0.5,0));
        agregar(new BrazoVertical(num_cubos_vertical));
        agregar(MAT_Traslacion(0, num_cubos_vertical+sqrt(1-0.5*0.5),0));
        agregar(new BrazoHorizontal(num_cubos_horizontal));
    }
};

#endif
