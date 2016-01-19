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

    NodoEscena( Objeto3D * obj);
    NodoEscena ( Matriz4f * mat);
};


// Clase nodo del grafo de escena

class Nodo : public Objeto3D{
protected:
    stack<EntradaNodo> escena;
public:
    virtual void visualizar ( ContextoVis & cv);

    void push (EntradaNodo *entrada);
};

#endif
