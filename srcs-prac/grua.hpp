#include "practica1.hpp"
#include "practica2.hpp"
#include "escena.hpp"
#include <iostream>
#include <cctype>

#ifndef _GRUA_H_
#define _GRUA_H_


class Viga : public NodoEscena{
public:
    Viga(double longitud = 1.0);
};


class VigaDiagonal : public NodoEscena{
public:
    VigaDiagonal(double longitud = 1.0);
};


class ParColumnas : public NodoEscena{
public:
    ParColumnas();
};


class ArmazonBasico : public NodoEscena{
public:
    ArmazonBasico();
};


class ParArmazon : public NodoEscena{
public:
    ParArmazon();
};


class TiraTriangulada : public NodoEscena{
public:
    TiraTriangulada(unsigned num_cubos);
};


class ParTiraTriangulada : public NodoEscena{
public:
    ParTiraTriangulada(unsigned num_cubos);
};


class BrazoVertical: public NodoEscena{
public:
    BrazoVertical(unsigned num_cubos);
};


class LateralBrazoHorizontal: public NodoEscena{
public:
    LateralBrazoHorizontal(unsigned num_cubos);
};


class BrazoHorizontal: public NodoEscena{
public:
    BrazoHorizontal(unsigned num_cubos);
};

class TrianguloRemate : public NodoEscena{
public:
    TrianguloRemate();
};

class RemateBrazoHorizontal : public NodoEscena{
public:
    RemateBrazoHorizontal();
};

class ContrapesoBrazoHorizontal : public NodoEscena{
public:
    ContrapesoBrazoHorizontal(unsigned longitud);
};

class CablesTensores : public NodoEscena{
public:
    CablesTensores(unsigned longitud_brazo, unsigned longitud_contrapeso);
};

class BaseGrua : public NodoEscena{
public:
    BaseGrua();
};

class HiloGancho : public NodoEscena{
protected:
    double longitud;
    unsigned indice_escalado;
public:
    HiloGancho(double longitud);

    void aumentarLongitud(double offset);
};

class CableGancho : public NodoEscena{
protected:
    double longitud;
    unsigned indice_traslacion, indice_hilo;
public:
    CableGancho(double longitud);

    void aumentarLongitud(double offset);
};

class SujecionCable : public NodoEscena{
public:
    SujecionCable();
};


class Gancho : public NodoEscena{
    unsigned indice_gancho;
    unsigned indice_traslacion;
    double traslacion;
public:
    Gancho(unsigned longitud, double traslacion);

    void aumentarLongitud(double offset);

    void aumentarTraslacion(double offset);
};

class Grua : public NodoEscena{
protected:
    unsigned longitud_vertical;
    unsigned longitud_gancho;
    unsigned longitud_horizontal;
    unsigned longitud_contrapeso;
    double giro_cabeza;

    unsigned indice_giro_cabeza;
    unsigned indice_gancho;
    unsigned indice_altura;
public:
    Grua(unsigned longitud_vertical, unsigned longitud_gancho,
         unsigned longitud_horizontal, unsigned longitud_contrapeso, double giro_cabeza);

    void aumentarTraslacionGancho(double offset);

    void aumentarLongitudGancho(double offset);

    void girarCabezaGrua(double offset);
};

#endif
