#include "MallaInd.hpp"
#include "file_ply_stl.hpp"
#include <cmath>

#ifndef _MALLAREV_H_
#define _MALLAREV_H_
const double PI = 3.1415926535897932;

// Clase mallas de revolución
class MallaRevol : public MallaInd {
public:
    // Constructor
    // Se debe especificar: nombre completo del archivo a leer
    //                      número de copias del perfil

    MallaRevol( const char * nombre_arch, unsigned nperfiles ) ;
};

#endif
