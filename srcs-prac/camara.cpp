#include "camara.hpp"

static const double udesp = 5;

void CamaraInteractiva::moverHV( int nh, int nv ){
    V[0][0] += nh*udesp;
    V[0][1] += nv*udesp;
}
