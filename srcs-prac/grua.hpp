#include "practica1.hpp"
#include "practica2.hpp"
#include "escena.hpp"
#include <iostream>
#include <cctype>

#ifndef _GRUA_H_
#define _GRUA_H_


class Viga : public NodoGrafoEscena{
public:
    Viga(double longitud = 1.0);
};


class VigaDiagonal : public NodoGrafoEscena{
public:
    VigaDiagonal(double longitud = 1.0);
};


class ParColumnas : public NodoGrafoEscena{
public:
    ParColumnas();
};


class ArmazonBasico : public NodoGrafoEscena{
public:
    ArmazonBasico();
};


class TiraTriangulada : public NodoGrafoEscena{
public:
    TiraTriangulada(unsigned num_cubos);
};


class ParTiraTriangulada : public NodoGrafoEscena{
public:
    ParTiraTriangulada(unsigned num_cubos);
};


class BrazoVertical: public NodoGrafoEscena{
public:
    BrazoVertical(unsigned num_cubos);
};


class LateralBrazoHorizontal: public NodoGrafoEscena{
public:
    LateralBrazoHorizontal(unsigned num_cubos);
};


class BrazoHorizontal: public NodoGrafoEscena{
public:
    BrazoHorizontal(unsigned num_cubos);
};

class TrianguloRemate : public NodoGrafoEscena{
public:
    TrianguloRemate();
};

class RemateBrazoHorizontal : public NodoGrafoEscena{
public:
    RemateBrazoHorizontal();
};

class ContrapesoBrazoHorizontal : public NodoGrafoEscena{
public:
    ContrapesoBrazoHorizontal(unsigned longitud);
};

class CablesTensores : public NodoGrafoEscena{
public:
    CablesTensores(unsigned longitud_brazo, unsigned longitud_contrapeso);
};

class BaseGrua : public NodoGrafoEscena{
public:
    BaseGrua();
};

class HiloGancho : public NodoGrafoEscena{
protected:
    double longitud;
    double max_longitud, min_longitud;
    unsigned indice_escalado;
public:
    HiloGancho(double longitud, double min_longitud, double max_longitud);

    void aumentarLongitud(double offset);
};

class SujecionCable : public NodoGrafoEscena{
public:
    SujecionCable();
};

class Gancho : public NodoGrafoEscena{
protected:
    unsigned indice_traslacion, indice_hilo, indice_cable;
    double traslacion;
    double max_traslacion, min_traslacion;
    double longitud;
    double max_longitud, min_longitud;
public:
    Gancho(double longitud, double traslacion);

    void aumentarLongitud(double offset);

    void aumentarTraslacion(double offset);
};

class Grua : public NodoGrafoEscena{
protected:
    double giro_cabeza;
    unsigned indice_giro_cabeza;
    unsigned indice_gancho;
public:
    Grua(unsigned longitud_vertical, unsigned longitud_gancho,
         unsigned longitud_horizontal, unsigned longitud_contrapeso, double giro_cabeza);

    void aumentarTraslacionGancho(double offset);

    void aumentarLongitudGancho(double offset);

    void girarCabezaGrua(double offset);
};

#endif
