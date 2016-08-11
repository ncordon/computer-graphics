#include "Objeto3D.hpp"

std::string Objeto3D::nombre(){
    return nombre_obj;
}
void Objeto3D::changeColor(Tupla3f new_color){
    color = new_color;
}
