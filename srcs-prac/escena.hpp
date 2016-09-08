#include "matrices-tr.hpp"
#include "aux.hpp"
#include "lighting.hpp"
#include "Objeto3D.hpp"
using namespace std;

#ifndef _ESCENA_H_
#define _ESCENA_H_

// Entrada de un nodo. Puede ser un objeto o una transformación
struct EntradaNodo{
    enum TipoNodo {TRANSFORMACION, OBJETO, MATERIAL, NODO};

    TipoNodo tipoE;

    union{
        Material * material;
        Objeto3D * objeto;
        Matriz4f * transformacion;
    };

    // Crea el nodo con un objeto 3D
    EntradaNodo(Objeto3D *obj, bool es_nodo) : objeto(obj){
        if (es_nodo)
            tipoE = NODO;
        else
            tipoE = OBJETO;
    }

    // Crea el nodo con una matriz de transformación
    EntradaNodo(const Matriz4f &mat) : transformacion(new Matriz4f(mat)){
        tipoE = TRANSFORMACION;
    }

    EntradaNodo(Material* mat) : material(mat){
        tipoE = MATERIAL;
    }

    bool esTransformacion(){
        return (tipoE == TRANSFORMACION);
    }


    bool esObjeto(){
        return (tipoE == OBJETO || tipoE == NODO);
    }

    bool esNodo(){
        return (tipoE == NODO);
    }
};


// Clase nodo del grafo de escena
class NodoGrafoEscena : public Objeto3D{
protected:
    // Pila de entradas
    vector<EntradaNodo> entradas;
public:
    unsigned char identificador ;  // identificador entero (0 si el nodo no se selecciona)
    Tupla3f       centro        ;  // punto central del objeto, en coordenadas de mundo

    NodoGrafoEscena() : identificador(0){};

    virtual void visualizar(ContextoVis &cv);

    // Introduce una nueva entrada
    void agregar(EntradaNodo *entrada){
        entradas.push_back(*entrada);
    }

    // Agrega un objeto 3D
    void agregar(Objeto3D *obj, bool es_nodo = false){
        entradas.push_back(EntradaNodo(obj, es_nodo));
    }

    // Agrega una matriz de transformación
    void agregar(const Matriz4f &mat){
        entradas.push_back(EntradaNodo(mat));
    }

    // Agrega una textura
    void agregar(Material* mat){
        entradas.push_back(EntradaNodo(mat));
    }

    // Devuelve el nodo de identificador identBuscado, NULL si no existe
    NodoGrafoEscena * buscarNodoConIdent( unsigned char identBuscado );

    // Modo selección de objeto
    void modoSeleccion();
};

#endif
