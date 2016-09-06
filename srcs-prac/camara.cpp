#include "camara.hpp"

static const double udesp = 5;
static const double urot = PI/6;
static const double dmin = 1;
static const double porc = 1;

ViewFrustum::ViewFrustum(){
    persp = false;
    left = bottom = -1;
    right = top = 1;
    near = 0;
    far = 2;

    /*
    Matriz4f traslacion = MAT_Traslacion(
        -0.5*(left + right),
        -0.5*(top + bottom),
        -0.5*(far + near)
    );

    Matriz4f escalado = MAT_Escalado(
         2/(right - left),
         2/(top - bottom),
        -2/(far - near)
    );

    matrizProy = escalado * traslacion;
    */
    matrizProy = MAT_Ortografica(left, right, bottom, top, near, far);
}

ViewFrustum::ViewFrustum( float hfovy, float aspect, float zNear, float zFar ){
    persp = true;
    top = zNear * tan(0.5 * hfovy * M_PI/360.0);
    right = top * aspect;
    bottom = -top;
    left = -right;

    matrizProy = MAT_Frustum(left, right, bottom, top, near, far);
}


MarcoCoorVista::MarcoCoorVista(){
    org = Tupla3f(0,0,0);
    eje[0] = Tupla3f(1,0,0);
    eje[1] = Tupla3f(0,0,1);
    eje[2] = Tupla3f(0,1,0);

    for (int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            if(i==j)
                matrizML(i,j) = matrizLM(i,j) = 1;
            else
                matrizML(i,j) = matrizLM(i,j) = 0;
}

MarcoCoorVista::MarcoCoorVista( const Tupla3f &pfoco, const Tupla3f &paten, const Tupla3f &pvup){
    org = pfoco;

    eje[2] = (pfoco - paten).normalized();
    eje[0] = pvup.cross(eje[2]).normalized();  // eje Z apunta en la dir. contraria a la camara
    eje[1] = eje[2].cross( eje[0] );                     // eje Y perpendicular a los otros dos.

    Matriz4f  traslacion = MAT_Traslacion( -pfoco[X], -pfoco[Y], -pfoco[Z] ),
              rot = MAT_Ident() ; // matriz de cambio de base mundo --> camara

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
              rot(i,j) = eje[i](j);

    matrizML = rot * traslacion;
}

Camara::Camara(){}


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
        //V[0][0] += nh*udesp;
        //V[0][1] += nv*udesp;
    }
}

void CamaraInteractiva::desplaZ( int nz ){
    if(examinar){
        dist = dmin + (dist-dmin)*(1.0-nz*porc/100.0);
    }
    else{
        //V[0][2] += nz*udesp;
    }
}

void Camara::fijarMVPOpenGL(){
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glMultMatrixf(mcv.matrizML);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glMultMatrixf(vf.matrizProy);
}
