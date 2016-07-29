#include "matrices-tr.hpp"
#include "aux.hpp"
#include "Objeto3D.hpp"
using namespace std;

#ifndef _ESCENA_H_
#define _ESCENA_H_

// Entrada de un nodo. Puede ser un objeto o una transformación
struct EntradaNodo{
    bool es_transformacion;

    union{
        Objeto3D * objeto;
        Matriz4f * transformacion;
    };

    // Crea el nodo con un objeto 3D
    EntradaNodo(Objeto3D *obj) : objeto(obj){
        es_transformacion = false;
    }
    // Crea el nodo con una matriz de transformación
    EntradaNodo(const Matriz4f &mat) : transformacion(new Matriz4f(mat)){
        es_transformacion = true;
    }
    // Destructor
    // ¿Esto funcionará?
    //~EntradaNodo();
};


// Clase nodo del grafo de escena
class NodoEscena : public Objeto3D{
protected:
    // Pila de entradas
    vector<EntradaNodo> entradas;
public:
    virtual void visualizar(unsigned modo);

    // Introduce una nueva entrada
    void agregar(EntradaNodo *entrada){
        entradas.push_back(*entrada);
    }

    // Agrega un objeto 3D
    void agregar(Objeto3D *obj){
        entradas.push_back(EntradaNodo(obj));
    }

    // Agrega una matriz de transformación
    void agregar(const Matriz4f &mat){
        entradas.push_back(EntradaNodo(mat));
    }
};

#endif
