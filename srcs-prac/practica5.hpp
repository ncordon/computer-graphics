// *********************************************************************
// **
// ** Informática Gráfica, curso 2015-16
// ** Práctica 3
// **
// *********************************************************************

#ifndef IG_PRACTICA5_HPP
#define IG_PRACTICA5_HPP
//#include "MallaInd.hpp"
#include "stdlib.h"
#include <iostream>
#include <cctype>

using namespace std;

void P5_Inicializar( int argc, char *argv[] ) ;
bool P5_FGE_PulsarTeclaNormal(  unsigned char tecla ) ;
bool P5_FGE_PulsarTeclaEspecial(  unsigned char tecla ) ;
void P5_DibujarObjetos( unsigned modo ) ;
void P5_FijarMVPOpenGL();

#endif
