// *********************************************************************
// **
// ** Informática Gráfica, curso 2015-16
// ** Práctica 1  (implementación)
// **
// *********************************************************************

#include "aux.hpp"
#include "tuplasg.hpp"   // Tupla3f
#include "practica1.hpp"

// ---------------------------------------------------------------------
// declaraciones de estructuras de datos....
unsigned objeto_activo = 0 ; // objeto activo: cubo (0), tetraedro (1), otros....
std::vector<MallaInd> objetos;


Cubo::Cubo(){
    nombre_obj = "Mi cubo";

    // Vértices que conforman el cubo
    vertices.push_back(Tupla3f(-0.5, -0.5, 0.5));
    vertices.push_back(Tupla3f(0.5, -0.5, 0.5));
    vertices.push_back(Tupla3f(0.5, 0.5, 0.5));
    vertices.push_back(Tupla3f(-0.5, 0.5, 0.5));
    vertices.push_back(Tupla3f(-0.5, -0.5, -0.5));
    vertices.push_back(Tupla3f(0.5, -0.5, -0.5));
    vertices.push_back(Tupla3f(0.5, 0.5, -0.5));
    vertices.push_back(Tupla3f(-0.5, 0.5, -0.5));

    // Triángulos que conforman las caras.
    // En sentido antihorario, las caras laterales.
    // Después la tapa superior e inferior
    caras.push_back(Tupla3i(0, 2, 3));
    caras.push_back(Tupla3i(0, 1, 2));
    caras.push_back(Tupla3i(1, 6, 2));
    caras.push_back(Tupla3i(1, 5, 6));
    caras.push_back(Tupla3i(5, 7, 6));
    caras.push_back(Tupla3i(5, 4, 7));
    caras.push_back(Tupla3i(4, 7, 3));
    caras.push_back(Tupla3i(4, 3, 0));
    caras.push_back(Tupla3i(3, 6, 7));
    caras.push_back(Tupla3i(3, 2, 6));
    caras.push_back(Tupla3i(0, 4, 5));
    caras.push_back(Tupla3i(0, 5, 1));
}

Tetraedro::Tetraedro(){
    nombre_obj = "Mi tetraedro";

    // Vértices que conforman el tetraedro
    vertices.push_back(Tupla3f(-0.5, -0.5, 0.5));
    vertices.push_back(Tupla3f(0.5, -0.5, 0.5));
    vertices.push_back(Tupla3f(-0.5, -0.5, -0.5));
    vertices.push_back(Tupla3f(-0.5, 0.5, -0.5));

    // Triángulos que conforman las caras
    // Primero tapa inferior
    // Después, en sentido antihorario, las caras laterales
    caras.push_back(Tupla3i(0, 1, 2));
    caras.push_back(Tupla3i(1, 3, 2));
    caras.push_back(Tupla3i(2, 0, 3));
    caras.push_back(Tupla3i(0, 1, 3));
}



// ---------------------------------------------------------------------
// Función para implementar en la práctica 1 para inicialización.
// Se llama una vez al inicio, cuando ya se ha creado la ventana e
// incializado OpenGL.

void P1_Inicializar( int argc, char *argv[]){
    objetos.push_back(Cubo());
    objetos.push_back(Tetraedro());
    objeto_activo = 0;
}

// ---------------------------------------------------------------------
// Función invocada al pulsar una tecla con la práctica 1 activa:
// (si la tecla no se procesa en el 'main').
//
//  - devuelve 'true' si la tecla se usa en esta práctica para cambiar
//    entre el cubo, el tetraedro u otros objetos (cambia el valor de
//    'objeto_activo').
//  - devuelve 'false' si la tecla no se usa en esta práctica (no ha
//    cambiado nada)

bool P1_FGE_PulsarTeclaNormal(unsigned char tecla){
    bool tecla_correcta = false;

    if (tecla == 'd'){
        objeto_activo += 1;
        objeto_activo %= objetos.size();
        tecla_correcta = true;
    }

    return tecla_correcta;
}


// ---------------------------------------------------------------------
// Función a implementar en la práctica 1  para dibujar los objetos
// modo: 0 - puntos, 1 - alambre, 2 - sólido, 3 - sólido ajedrez , >=4 otros....

void P1_DibujarObjetos(unsigned modo){
    objetos[objeto_activo].visualizar(modo);
}
