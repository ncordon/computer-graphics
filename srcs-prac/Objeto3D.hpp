#ifndef OBJETO3D_HPP
#define OBJETO3D_HPP
#include "tuplasg.hpp"   // Tupla3f
#include <string>


// clase abstracta para objetos 3D visualizables con OpenGL
class Objeto3D{
protected:
    std::string nombre_obj ; // nombre asignado al objeto
    Tupla3f color;
public:
    Objeto3D() : color(Tupla3f(0.2,0.2,0.2)){}
    void changeColor(Tupla3f new_color);
    virtual void visualizar(unsigned modo_vis) = 0 ; // visualizar el objeto con OpenGL
    std::string nombre() ;  // devuelve el nombre del objeto
};

#endif
