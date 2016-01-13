#ifndef OBJETO3D_HPP
#define OBJETO3D_HPP
#include <string>

using namespace std;

// clase abstracta para objetos 3D visualizables con OpenGL
class Objeto3D{
protected:
    string nombre_obj ; // nombre asignado al objeto
public:
    virtual void visualizar( unsigned modo_vis ) = 0 ; // visualizar el objeto con OpenGL
    string nombre() ;  // devuelve el nombre del objeto
};

#endif
