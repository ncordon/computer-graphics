// *********************************************************************
// **
// ** Informática Gráfica, curso 2015-16
// ** Práctica 3
// **
// *********************************************************************

#ifndef IG_PRACTICA4_HPP
#define IG_PRACTICA4_HPP
//#include "MallaInd.hpp"
#include "stdlib.h"
#include <iostream>
#include "practica1.hpp"
#include "practica2.hpp"
#include "practica3.hpp"
#include <cctype>

using namespace std;

void P4_Inicializar( int argc, char *argv[] ) ;
bool P4_FGE_PulsarTeclaNormal(  unsigned char tecla ) ;
void P4_DibujarObjetos( unsigned modo ) ;


class PeonMadera : public NodoGrafoEscena{
public:
    PeonMadera();
};

class PeonBlanco : public NodoGrafoEscena{
public:
    PeonBlanco();
};


class PeonNegro : public NodoGrafoEscena{
public:
    PeonNegro();
};


class Lata : public NodoGrafoEscena{
public:
    Lata();
};

#endif
