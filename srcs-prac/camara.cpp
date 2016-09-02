#include "camara.hpp"

static const double udesp = 5;
static const double urot = PI/6;
static const double dmin = 1;
static const double porc = 1;

CamaraInteractiva::CamaraInteractiva(){
    examinar = false;
    aten = Tupla3f(0,0,0);
    long_rot = 0;
    lati_rot = 0;
}
void CamaraInteractiva::moverHV( int nh, int nv ){
    if(examinar){
        long_rot += nh*urot;
        lati_rot += nv*urot;
    }
    else{
        V[0][0] += nh*udesp;
        V[0][1] += nv*udesp;
    }
}

void CamaraInteractiva::desplaZ( int nz ){
    if(examinar){
        dist = dmin + (dist-dmin)*(1.0-nz*porc/100.0);
    }
    else{
        V[0][2] += nz*udesp;
    }
}
