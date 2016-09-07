#include "aux.hpp"
#include "matrices-tr.hpp"
#ifndef _CAMARA_H_
#define _CAMARA_H_

// marco de coordenadas (cartesiano) de la vista
class MarcoCoorVista{
public:
    Tupla3f org,        // origen del marco de coordenadas
            eje[3],     // ejes(0=X,1=Y, 2=Z) del marco de cc(ortonormales)
            pvup;       //
    Matriz4f matrizML;  // matriz marco->mundo
    Matriz4f matrizLM;  // matriz marco->mundo

    //foco en origen, mirando hacia Z-, vup=Y+
    MarcoCoorVista();
    // constructor: mismos parámetros que gluLookAt
    MarcoCoorVista( const Tupla3f &pfoco, const Tupla3f &paten, const Tupla3f &pvup);
};


class ViewFrustum{
public:
    bool persp; // true para perspectiva, false para ortográfica
    float left, right,  // extensión en X(left<right)
          bottom, top,  // extensión en Y(bottom<top)
          near, far;    // extensión en Z(rama negativa) (0 < near < far)
    Matriz4f matrizProy; // matriz de proyección P: cc. cámara ===> cc.recortado

    ViewFrustum(); // view-frustum ortográfico de lado 2, centro en (0,0,0)
    // crea view-frustum perspectiva, mismos parámetros que gluPerspective
    ViewFrustum( float hfovy, float aspect, float zNear, float zFar );
};


class Camara{
public:
    MarcoCoorVista mcv; // marco de coordenadas de la vista
    ViewFrustum vf;     // parámetros de la proyección

    Camara();           // usa constructores por defecto para mc y vf
    void fijarMVPOpenGL(); // fijar matrices MODELVIEW y PROJECTION de OpenGL
};

class CamaraInteractiva : public Camara{
public:
    bool    examinar ; // modo: true --> examinar, false --> primera persona (inicialmente false)
    float   long_rot ,     // en modo examinar: ángulo (en radianes) en torno al eje Y (longitud) (inic. 0)
            lati_rot ;     // en modo examinar: ángulo (en radianes) en torno al eje X (latitud) (inic. 0))
    Tupla3f aten ;     // en modo examinar: punto de atención (inicialmente el origen)
    float   dist ;     // en modo examinar: distancia entre el punto de atención y el observador

    // constructor por defecto, deja la cámara en modo primera persona,
    // observador en el origen, marco de la cámara coincide con marco del mundo.
    CamaraInteractiva() ;

    //  métodos para manipular (desplazar o rotar) la cámara
    void moverHV( int nh, int nv ) ; // desplazar o rotar la cámara en horizontal/vertical
    void desplaZ( int nz );          // desplazar en el eje Z de la cámara (hacia adelante o hacia detrás)
    void fijarAten( const Tupla3f & nuevoAten ) ; // fija el nuevo punto de atención y pasa al modo examinar
    void modoPrimeraPersona() ;                   // pasa al modo primera persona
};

#endif
