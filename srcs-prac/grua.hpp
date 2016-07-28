#include "practica1.hpp"
#include "practica2.hpp"
#include "escena.hpp"
#include <iostream>
#include <cctype>

#ifndef _GRUA_H_
#define _GRUA_H_

class ParColumnas : public NodoEscena{
public:
    ParColumnas();
};


class ArmazonBasico : public NodoEscena{
public:
    ArmazonBasico();
};

class Viga : public NodoEscena{
public:
    Viga(double longitud = 1.0);
};


class Grua : public NodoEscena{
public:
    Grua(){
        agregar(new ArmazonBasico);
    }
};

#endif
