// *********************************************************************
// **
// ** Informática Gráfica, curso 2015-16
// ** Práctica 1  (declaraciones públicas)
// **
// *********************************************************************

#ifndef IG_PRACTICA1_HPP
#define IG_PRACTICA1_HPP
#include "MallaInd.hpp"


class Cubo : public MallaInd{
public:
    Cubo();
};

class Tetraedro : public MallaInd{
public:
    Tetraedro();
};

class Cilindro : public MallaInd{
public:
    Cilindro();
};

class Cono : public MallaInd{
public:
    Cono();
};

void P1_Inicializar( int argc, char *argv[] ) ;
bool P1_FGE_PulsarTeclaNormal(  unsigned char tecla ) ;
void P1_DibujarObjetos( unsigned modo ) ;

#endif
