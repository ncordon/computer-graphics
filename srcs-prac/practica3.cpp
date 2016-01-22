#include "Practica3.hpp"



// Grado de libertad actual seleccionado en el programa
int p3_degree;




void P3_Inicializar( int argc, char *argv[] ){
    p3_degree = 0;

}



bool P3_FGE_PulsarTeclaNormal(  unsigned char tecla ){
    bool redibuja = true;
    
    switch(toupper(tecla)){
    case 'G':
        p3_fdegree += 1;
        p3_fdegree %= 3;

        break;
    case '>':
        // Aumentar grado de libertad

        // Si se sobrepasa el máximo, no redibujar
        break;
    case '<':

        break;

    default:
        redibujar = false;        
    }


    
    return redibujar;
}
