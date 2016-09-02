#include "aux.hpp"
#include "matrices-tr.hpp"
#ifndef _CAMARA_H_
#define _CAMARA_H_

class Camara{
    public:
        GLfloat V[3][4]; // o, a, u
            // glMatrixMode( GL_MODELVIEW );
            // glLoadIdentity();
            // glMultMatrixf( V );
            //void gluLookAt
            //    ( GLdouble o x , GLdouble o y , GLdouble o z ,
            //    GLdouble a x , GLdouble a y , GLdouble a z ,
            //    GLdouble u x , GLdouble u y , GLdouble u z
            //    ) ;
};

class CamaraInteractiva : public Camara
{
   public:
   // constructor por defecto, deja la cámara en modo primera persona,
   // observador en el origen, marco de la cámara coincide con marco del mundo.
   CamaraInteractiva() ;

   //  métodos para manipular (desplazar o rotar) la cámara
   void moverHV( int nh, int nv ) ; // desplazar o rotar la cámara en horizontal/vertical
   void desplaZ( int nz );          // desplazar en el eje Z de la cámara (hacia adelante o hacia detrás)
   void fijarAten( const Tupla3f & nuevoAten ) ; // fija el nuevo punto de atención y pasa al modo examinar
   void modoPrimeraPersona() ;                   // pasa al modo primera persona
} ;

#endif
