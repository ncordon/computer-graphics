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
public:
    virtual void visualizar(unsigned modo_vis);
};

#endif
