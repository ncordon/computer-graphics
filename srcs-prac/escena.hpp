#ifndef _ESCENA_h_
#define _ESCENA_h_
#include "matrices-tr.hpp"
#include <stack>

using namespace std;

// Entrada de un nodo. Puede ser un objeto o una transformación

struct EntradaNodo{
    bool es_transformacion;

    union{
        Objeto3D * objeto;
        Matriz4f * matriz;
    }

    // Crea el nodo con un objeto 3D
    EntradaNodo( Objeto3D * obj);
    // Crea el nodo con una matriz de transformación
    EntradaNodo( Matriz4f * mat);
    // Destructor
    ~EntradaNodo();
};


// Clase nodo del grafo de escena

class NodoEscena : public Objeto3D{
protected:
    // Pila de entradas
    stack<EntradaNodo*> escena;
public:
    virtual void visualizar ();

    // Introduce una nueva entrada
    inline void push (EntradaNodo *entrada){
        escena.push(entrada);
    }
    
    // Saca la última entrada del nodo
    inline void.pop (){
        escena.pop();
    }
};

#endif
