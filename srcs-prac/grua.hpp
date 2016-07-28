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

class BrazoHorizontal: public NodoEscena{
public:
    BrazoHorizontal(unsigned num_cubos);
};

class Grua : public NodoEscena{
public:
    Grua(){
        agregar(new BrazoVertical(10));
        agregar(new BrazoHorizontal(10));
    }
};

#endif
