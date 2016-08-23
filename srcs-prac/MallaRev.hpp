#include "MallaInd.hpp"
#include "file_ply_stl.hpp"
#include <cmath>

#ifndef _MALLAREV_H_
#define _MALLAREV_H_

// Clase mallas de revolución
class MallaRev : public MallaInd {
protected:
    void calcularTexturas(unsigned n_perfiles, unsigned n_vertices);
public:
    // Constructor
    // Se debe especificar: nombre completo del archivo a leer
    //                      número de copias del perfil
    //                      si se desea especificar coordenadas de textura o no

    MallaRev( const char * nombre_arch, unsigned n_perfiles, bool con_textura = false) ;
};

#endif
