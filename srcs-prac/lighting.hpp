#include "aux.hpp"
#include "tuplasg.hpp"
#include "jpg_imagen.hpp"
#ifndef _CUSTOM_H_
#define _CUSTOM_H_

class Material{
public:
    virtual void activar( ) = 0;
};


// ---------------------------------------------------------------------
// Imagen de textura

class Textura{
public:
    GLuint        id_text;    // identificador OpenGL de la textura
    jpg::Imagen * img = NULL; // puntero a imagen con los texels
    unsigned      mgct;       // modo de gen. cc.tt. (0 = desactivado, 1 = objeto, 2 = camara)
    float         cs[4],ct[4]; // coeficientes para generación de coords. de textura

    void activar(  );          // activa textura en el cauce fijo de OpenGL
    Textura( const std::string & archivoJPG ); // crea un textura a partir de un archivo
};

// ---------------------------------------------------------------------
// Parámetros de un material estándar (Amb.+Diffuso+Phong)

class MaterialEstandar  : public Material{
public:
    Textura * text = NULL; // puntero a la textura (NULL si no hay)
    Tupla4f   color[4];    // colores: 0=emisión, 1=ambiental, 2=difuso, 3=especular
    float     exponente;   // exponente para la componente pseudo-especular

    virtual void activar(  );// activa material en el cauce fijo
    //   si tiene textura: activa uso de la textura 'text'
    //   si no tiene textura: desactiva uso de texturas
};



// ---------------------------------------------------------------------
// Parámetros que definen una fuente de luz

class FuenteLuz{
public:
    Tupla4f  posvec;       // posición (si w=1) o vector (w=0)
    Tupla4f  colores[3];   // colores: 0=ambiental, 1=difuso, 2=especular.
    float    long_rot, lat_rot;      // ángulos de rotación (fuente direccional modificable interactivamente)
    void activar( int i ); // activa la fuente de luz (con número GL_LIGHT0+i)
};

// ---------------------------------------------------------------------
// Colección de (hasta 8) fuentes de luz.

class ColeccionFL{
public:
    std::vector<FuenteLuz *> fuentes;  // vector de fuentes de luz
    void activar(  );                  // activa todas las fuentes de luz en el cauce fijo
    //   (antes de eso activa iluminación y la configura)
};


// Materiales de la práctica 4

class MaterialLata : public MaterialEstandar{
public:
    MaterialLata();
};

class MaterialTapasLata : public MaterialEstandar{
public:
    MaterialTapasLata();
};

class MaterialPeonMadera : public MaterialEstandar{
public:
    MaterialPeonMadera();
};

class MaterialPeonBlanco : public MaterialEstandar{
public:
    MaterialPeonBlanco();
};

class MaterialPeonNegro : public MaterialEstandar{
public:
    MaterialPeonNegro();
};

// Fuentes de luz de la práctica 4

class FuenteDireccional : public FuenteLuz{
public:
    FuenteDireccional( float alpha_inicial, float beta_inicial );
    void variarAngulo( int i, unsigned angulo, float incremento );  // angulo=0 --> variar alpha, angulo=1 --> variar beta
};

class FuentePosicional : public FuenteLuz{
public:
    FuentePosicional( const Tupla3f & posicion );
};

#endif
