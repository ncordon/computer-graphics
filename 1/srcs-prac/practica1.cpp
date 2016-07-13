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
int num_caras = 50;
const double PI = 3.14159265359;
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

Cilindro::Cilindro(){
    nombre_obj = "Mi cilindro";
    double angulo = 2*PI/num_caras;
    int tapa_sup, tapa_inf, inf, sup;

    for (int i=0; i<num_caras; i++){
        // Vértice de la cara inferior
        vertices.push_back(0.5f*Tupla3f(cos(angulo*i), -1, sin(angulo*i)));
        // Vértice de la cara superior
        vertices.push_back(0.5f*Tupla3f(cos(angulo*i), 1, sin(angulo*i)));
    }

    // Vértices del eje central
    tapa_inf = vertices.size();
    tapa_sup = tapa_inf+1;
    vertices.push_back(Tupla3f(0,-0.5,0));
    vertices.push_back(Tupla3f(0,0.5,0));

    for (int i=0; i<num_caras; i++){
        inf = i*2;
        sup = inf+1;
        // Laterales
        caras.push_back(Tupla3i(inf, (inf+2)%(2*num_caras), (inf+3)%(2*num_caras)));
        caras.push_back(Tupla3i(sup, (sup+2)%(2*num_caras), inf));
        // Tapaderas
        if (i%2==0){
            caras.push_back(Tupla3i(sup, (sup+2)%(2*num_caras), tapa_sup));
            caras.push_back(Tupla3i(inf, (inf+2)%(2*num_caras), tapa_inf));
        }
        else{
            caras.push_back(Tupla3i(inf, (inf+2)%(2*num_caras), tapa_inf));
            caras.push_back(Tupla3i(sup, (sup+2)%(2*num_caras), tapa_sup));
        }
    }
}


Cono::Cono(){
    nombre_obj = "Mi cono";
    double angulo = 2*PI/num_caras;
    int pico, tapa_inf;

    for (int i=0; i<num_caras; i++){
        // Vértice de la cara inferior
        vertices.push_back(0.5f*Tupla3f(cos(angulo*i), -1, sin(angulo*i)));
    }

    // Vértices del eje central
    tapa_inf = vertices.size();
    pico = tapa_inf+1;
    vertices.push_back(Tupla3f(0,-0.5,0));
    vertices.push_back(Tupla3f(0,0.5,0));

    for (int i=0; i<num_caras; i++){
        // Laterales
        if (i%2==0){
            // Laterales
            caras.push_back(Tupla3i(i, (i+1)%num_caras, pico));
            // Tapadera
            caras.push_back(Tupla3i(i, (i+1)%num_caras, tapa_inf));        }
        else{
            // Tapadera
            caras.push_back(Tupla3i(i, (i+1)%num_caras, tapa_inf));
            // Laterales
            caras.push_back(Tupla3i(i, (i+1)%num_caras, pico));
        }
    }
}

//Toro::Toro(){
//
//}


// ---------------------------------------------------------------------
// Función para implementar en la práctica 1 para inicialización.
// Se llama una vez al inicio, cuando ya se ha creado la ventana e
// incializado OpenGL.

void P1_Inicializar( int argc, char *argv[]){
    objetos.push_back(Cubo());
    objetos.push_back(Tetraedro());
    objetos.push_back(Cilindro());
    objetos.push_back(Cono());
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
