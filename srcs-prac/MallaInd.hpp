#include "Objeto3D.hpp"
#include <vector>
#include "tuplasg.hpp"
#include "aux.hpp"

#ifndef _MALLAIND_H_
#define _MALLAIND_H_
const double PI = 3.1415926535897932;

// clase para mallas indexadas o mallas TVT
class MallaInd : public Objeto3D{
protected:
    std::vector<Tupla3f> vertices;
    std::vector<Tupla3i> caras;

    // Vectores de normales de vértices y de caras
    std::vector<Tupla3f> normal_vertices;
    std::vector<Tupla3f> normal_caras;

    // Vector de texturas
    std::vector<Tupla2f> textura_coords;

    // Función para calcular las normales
    void calcularNormales();

    // Función para normalizar un vector
    Tupla3f normalize(Tupla3f m);
public:
    virtual void visualizar(ContextoVis &cv);
};

#endif
