#include "grua.hpp"

Viga::Viga(double longitud){
    agregar(MAT_Escalado(0.05,longitud,0.05));
    agregar(new Cilindro);
}


VigaDiagonal::VigaDiagonal(double longitud){
    agregar(MAT_Traslacion(1,0,0));
    agregar(MAT_Escalado(-1,1,1));
    agregar(MAT_Rotacion(-45,0,0,1));
    agregar(new Viga(longitud));
}


ParColumnas::ParColumnas(){
    agregar(new Viga);
    agregar(MAT_Traslacion(1,0,0));
    agregar(new Viga);
}


ArmazonBasico::ArmazonBasico(){
    agregar(new VigaDiagonal(sqrt(2)));
    agregar(new ParColumnas);
    agregar(MAT_Traslacion(1,0,0));
    agregar(MAT_Rotacion(90,0,0,1));
    agregar(new ParColumnas);
}


ParArmazon::ParArmazon(){
    agregar(new ArmazonBasico);
    agregar(MAT_Traslacion(1,0,1));
    agregar(MAT_Escalado(-1,1,1));
    agregar(new ArmazonBasico);
}



TiraTriangulada::TiraTriangulada(unsigned num_cubos){
    agregar(new ArmazonBasico);

    for(int i=0; i<num_cubos-1; i++){
        agregar(MAT_Traslacion(0,1,0));
        agregar(new ArmazonBasico);
    }
}

ParTiraTriangulada::ParTiraTriangulada(unsigned num_cubos){
    agregar(new TiraTriangulada(num_cubos));
    agregar(MAT_Traslacion(1,0,1));
    agregar(MAT_Rotacion(180,0,1,0));
    agregar(new TiraTriangulada(num_cubos));
}

BrazoVertical::BrazoVertical(unsigned num_cubos){
    agregar(new ParTiraTriangulada(num_cubos));
    agregar(MAT_Traslacion(0,0,1));
    agregar(MAT_Rotacion(90,0,1,0));
    agregar(new ParTiraTriangulada(num_cubos));
}

LateralBrazoHorizontal::LateralBrazoHorizontal(unsigned num_cubos){
    agregar(new TiraTriangulada(num_cubos));
    agregar(MAT_Traslacion(0,-1,0));
    agregar(new VigaDiagonal(sqrt(2)));
    agregar(MAT_Traslacion(1,0,0));
    agregar(new Viga);
}

BrazoHorizontal::BrazoHorizontal(unsigned num_cubos){
    NodoEscena *un_lateral = new NodoEscena;
    NodoEscena *otro_lateral = new NodoEscena;
    NodoEscena *tapa = new NodoEscena;
    un_lateral->agregar(MAT_Rotacion(-30,0,1,0));
    un_lateral->agregar(new LateralBrazoHorizontal(num_cubos-1));
    otro_lateral->agregar(MAT_Rotacion(30,0,1,0));
    otro_lateral->agregar(new LateralBrazoHorizontal(num_cubos-1));
    tapa->agregar(MAT_Traslacion(sqrt(1-0.5*0.5),-1,0.5));
    tapa->agregar(MAT_Rotacion(90,0,1,0));
    tapa->agregar(new TiraTriangulada(num_cubos));

    agregar(MAT_Traslacion(-1.0*(num_cubos-1),0,0.5));
    agregar(MAT_Rotacion(-90,0,0,1));
    agregar(un_lateral);
    agregar(otro_lateral);
    agregar(tapa);
}

TrianguloRemate::TrianguloRemate(){
    NodoEscena *viga_diag = new NodoEscena;
    double alpha = 90 - atan(2/0.5)/PI*180;

    viga_diag->agregar(MAT_Rotacion(-alpha,0,0,1));
    viga_diag->agregar(new Viga(sqrt(5)-0.2));
    agregar(MAT_Rotacion(alpha,1,0,0));
    agregar(viga_diag);
    // El 1.1 me permite corregir la anchura de la barra
    agregar(MAT_Traslacion(1,0,0));
    agregar(MAT_Escalado(-1,1,1));
    agregar(viga_diag);
}

RemateBrazoHorizontal::RemateBrazoHorizontal(){
    agregar(new TrianguloRemate);
    agregar(MAT_Traslacion(0,0,1));
    agregar(MAT_Escalado(1,1,-1));
    agregar(new TrianguloRemate);
}


ContrapesoBrazoHorizontal::ContrapesoBrazoHorizontal(unsigned longitud){
    NodoEscena *contrapeso = new NodoEscena;

    contrapeso->agregar(MAT_Escalado(2,-1,1));
    contrapeso->agregar(new Cubo);

    agregar(MAT_Traslacion(longitud+1,0,0));
    agregar(MAT_Escalado(-1,1,1));
    agregar(contrapeso);
    agregar(MAT_Escalado(longitud,0.1,1));
    agregar(new Cubo);
}

CablesTensores::CablesTensores(unsigned longitud_brazo, unsigned longitud_contrapeso){
    double offset_dcha = 2 - 0.1 - sqrt(1-0.5*0.5);
    double longitud_dcha = sqrt((longitud_contrapeso-1)*(longitud_contrapeso-1) + 4);
    double longitud_izda = sqrt((longitud_brazo-1)*(longitud_brazo-1) + offset_dcha*offset_dcha);
    double ang_contrapeso = -180+180*atan((longitud_contrapeso-1)/(2.0-0.1))/PI;
    double ang_brazo = 180-180*atan((longitud_brazo-1)/offset_dcha)/PI;

    NodoEscena *cable_dcha = new NodoEscena;
    cable_dcha->agregar(MAT_Rotacion(ang_contrapeso,0,0,1));
    cable_dcha->agregar(MAT_Escalado(0.1,longitud_dcha,0.1));
    cable_dcha->agregar(new Viga);

    NodoEscena *cable_izda = new NodoEscena;
    cable_izda->agregar(MAT_Rotacion(ang_brazo,0,0,1));
    cable_izda->agregar(MAT_Escalado(0.1,longitud_izda,0.1));
    cable_izda->agregar(new Viga);

    agregar(MAT_Traslacion(0.5,2-0.1,0.5));
    agregar(cable_dcha);
    agregar(cable_izda);
}

HiloGancho::HiloGancho(double longitud){
    this->longitud = longitud;
    indice_escalado = entradas.size();
    agregar(MAT_Escalado(0.3,longitud,0.3));
    agregar(new Viga);
}

void HiloGancho::aumentarLongitud(double offset){
    longitud = longitud + offset;
    entradas.at(indice_escalado) = MAT_Escalado(0.3,longitud,0.3);
}

CableGancho::CableGancho(double longitud){
    this->longitud = longitud;

    indice_traslacion = entradas.size();
    agregar(MAT_Traslacion(1,-longitud-0.1,0.5));
    indice_hilo = entradas.size();
    agregar(new HiloGancho(longitud));
    // Final del gancho
    agregar(MAT_Escalado(0.1,-0.2, 0.1));
    agregar(new Cilindro);
}

void CableGancho::aumentarLongitud(double offset){
    longitud = longitud + offset;
    entradas.at(indice_traslacion) = MAT_Traslacion(1,-1.0*longitud-0.1,0.5);
    HiloGancho *hilo = (HiloGancho*)entradas.at(indice_hilo).objeto;
    hilo->aumentarLongitud(offset);
}

SujecionCable::SujecionCable(){
    agregar(MAT_Escalado(2,-0.1,1));
    agregar(new Cubo);
}

Gancho::Gancho(unsigned longitud, double traslacion){
    this->traslacion = traslacion;
    this->max_traslacion = traslacion;
    this->min_traslacion = 3;

    indice_traslacion = entradas.size();
    agregar(MAT_Traslacion(-traslacion,0,0));
    agregar(new SujecionCable);
    indice_gancho = entradas.size();
    agregar(new CableGancho(longitud));
}

void Gancho::aumentarLongitud(double offset){
    CableGancho *cable = (CableGancho *)entradas.at(indice_gancho).objeto;
    cable->aumentarLongitud(offset);
}

void Gancho::aumentarTraslacion(double offset){
    traslacion = traslacion + offset;

    if(traslacion > max_traslacion)
        traslacion = max_traslacion;
    if(traslacion < min_traslacion)
        traslacion = min_traslacion;

    entradas.at(indice_traslacion) = MAT_Traslacion(-traslacion,0,0);
}

BaseGrua::BaseGrua(){
    agregar(MAT_Traslacion(-0.25,0,-0.25));
    agregar(MAT_Escalado(1.5,0.5,1.5));
    agregar(new Cubo);
}

Grua::Grua(unsigned longitud_vertical, unsigned longitud_gancho,
     unsigned longitud_horizontal, unsigned longitud_contrapeso, double giro_cabeza){
/*
    this->longitud_vertical = longitud_vertical;
    this->longitud_gancho = longitud_gancho;
    this->longitud_horizontal = longitud_horizontal;
    this->longitud_contrapeso = longitud_contrapeso;
*/
    this->giro_cabeza = giro_cabeza;

    agregar(new BaseGrua);
    agregar(MAT_Traslacion(0,0.5,0));
    agregar(new BrazoVertical(longitud_vertical));
    agregar(MAT_Traslacion(0, longitud_vertical,0));
    agregar(MAT_Traslacion(0.5,0,0.5));
    indice_giro_cabeza = entradas.size();
    agregar(MAT_Rotacion(giro_cabeza,0,1,0));
    agregar(MAT_Traslacion(-0.5,0,-0.5));
    agregar(new CablesTensores(longitud_horizontal, longitud_contrapeso));
    agregar(new RemateBrazoHorizontal);
    agregar(new ContrapesoBrazoHorizontal(longitud_contrapeso));
    indice_gancho = entradas.size();
    agregar(new Gancho(longitud_gancho, longitud_horizontal));
    agregar(MAT_Traslacion(0, sqrt(1-0.5*0.5),0));
    agregar(new BrazoHorizontal(longitud_horizontal));
    //agregar(new Gancho(longitud_gancho, longitud_horizontal));
}


void Grua::aumentarTraslacionGancho(double offset){
    Gancho *gancho = (Gancho *) entradas.at(indice_gancho).objeto;
    gancho->aumentarTraslacion(offset);
}

void Grua::aumentarLongitudGancho(double offset){
    Gancho *gancho = (Gancho *) entradas.at(indice_gancho).objeto;
    gancho->aumentarLongitud(offset);
}

void Grua::girarCabezaGrua(double offset){
    giro_cabeza = giro_cabeza + offset;

    while(giro_cabeza > 360){
        giro_cabeza -= 360;
    }

    while(giro_cabeza < 0){
        giro_cabeza += 360;
    }

    entradas.at(indice_giro_cabeza) = MAT_Rotacion(giro_cabeza,0,1,0);
}
