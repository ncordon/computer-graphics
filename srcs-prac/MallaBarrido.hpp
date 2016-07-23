#include "MallaInd.hpp"
#include "file_ply_stl.hpp"
#include <cmath>

#ifndef _MALLABARRIDO_H_
#define _MALLABARRIDO_H_

// Clase mallas de revolución
class MallaBarrido : public MallaInd {
public:
    // Constructor
    // Se debe especificar: nombre completo del archivo a leer
    //                      dir_volumen vector para generar el volumen.
    //                          Suponemos el vector normalizado, aunque no es necesario

    MallaBarrido(const char * nombre_arch, Tupla3f dir_volumen);
};

#endif
