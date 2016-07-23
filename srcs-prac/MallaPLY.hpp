#include "MallaInd.hpp"
#include "file_ply_stl.hpp"
#include <cmath>


#ifndef _MALLAPLY_H_
#define _MALLAPLY_H_

// Clase mallas indexadas obtenidas de un archivo PLY
class MallaPLY : public MallaInd {
public:
   // Constructor
   // Se debe especificar el nombre completo del archivo a leer
   MallaPLY( const char * nombre_arch ) ;
};

#endif
