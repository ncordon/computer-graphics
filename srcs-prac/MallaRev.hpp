#include "MallaInd.hpp"
#include "file_ply_stl.hpp"
#include <cmath>

#ifndef _MALLAREV_H_
#define _MALLAREV_H_

// Clase mallas de revolución
class MallaRev : public MallaInd {
public:
    // Constructor
    // Se debe especificar: nombre completo del archivo a leer
    //                      número de copias del perfil

    MallaRev( const char * nombre_arch, unsigned nperfiles ) ;
};

#endif
