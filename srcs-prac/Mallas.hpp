#include "Objeto3D.hpp"
#include <vector>
#include <cmath>
#include "tuplasg.hpp"
#include "aux.hpp"
#include "file_ply_stl.hpp"
using namespace std;

#ifndef _MALLAS_H_
#define _MALLAS_H_
const double PI = 3.1415926535897932;

// clase para mallas indexadas o mallas TVT
class MallaInd : public Objeto3D{
protected:
    vector<Tupla3f> vertices;
    vector<Tupla3i> caras;
public:
    virtual void visualizar( unsigned modo_vis );
};


// clase mallas indexadas obtenidas de un archivo PLY
class MallaPLY : public MallaInd
{
   public:
   // constructor
   // se debe especificar el nombre completo del archivo a leer
   MallaPLY( const char * nombre_arch ) ; 
};


// clase mallas indexadas obtenidas de un archivo PLY
class MallaRevol : public MallaInd
{
   public:
      // constructor
      // se debe especificar: el nombre completo del archivo a leer
      //                      el número de copias del perfil
      
      MallaRevol( const char * nombre_arch, unsigned nperfiles ) ; 
} ;

#endif
