#include "matrices-tr.hpp"
#include "aux.hpp"
#include "lighting.hpp"
#include "Objeto3D.hpp"
using namespace std;

#ifndef _ESCENA_H_
#define _ESCENA_H_

// Entrada de un nodo. Puede ser un objeto o una transformación
struct EntradaNodo{
    enum TipoNodo {es_transformacion, es_objeto, es_material};

    TipoNodo tipoE;

    union{
        Material * material;
        Objeto3D * objeto;
        Matriz4f * transformacion;
    };

    // Crea el nodo con un objeto 3D
    EntradaNodo(Objeto3D *obj) : objeto(obj){
        tipoE = es_objeto;
    }
    // Crea el nodo con una matriz de transformación
    EntradaNodo(const Matriz4f &mat) : transformacion(new Matriz4f(mat)){
        tipoE = es_transformacion;
    }

    EntradaNodo(Material* mat) : material(mat){
        tipoE = es_material;
    }

    bool esTransformacion(){
        return (tipoE == es_transformacion);
    }


    bool esObjeto(){
        return (tipoE == es_objeto);
    }
};


// Clase nodo del grafo de escena
class NodoGrafoEscena : public Objeto3D{
protected:
    // Pila de entradas
    vector<EntradaNodo> entradas;
public:
    virtual void visualizar(ContextoVis &cv);

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

    // Agrega una textura
    void agregar(Material* mat){
        entradas.push_back(EntradaNodo(mat));
    }
};

#endif
