#include "practica5.hpp"

static NodoGrafoEscena *p5_obj;
static ContextoVis p5_cv;
static vector< CamaraInteractiva > p5_camaras;
static int p5_camara_activa;

void P5_Inicializar( int argc, char *argv[] ){
    p5_obj = new NodoGrafoEscena;

    p5_obj->agregar(new Lata);
    p5_obj->agregar(MAT_Escalado(0.2,0.2,0.2));
    // Valor 1.4 tomado del peon.ply
    p5_obj->agregar(MAT_Traslacion(1,1.4,3));
    p5_obj->agregar(new PeonMadera);
    p5_obj->agregar(MAT_Traslacion(2.2,0,0));
    p5_obj->agregar(new PeonBlanco);
    p5_obj->agregar(MAT_Traslacion(2.2,0,0));
    p5_obj->agregar(new PeonNegro);

    // alzado
    p5_camaras.push_back(CamaraInteractiva());
    p5_camaras[0].mcv = MarcoCoorVista(Tupla3f(0.5,1,1), Tupla3f(0.5,1,0), Tupla3f(0,1,0));
    // perfil, con proyección ortográfica
    p5_camaras.push_back(CamaraInteractiva());
    p5_camaras[1].mcv = MarcoCoorVista(Tupla3f(-1,1,0), Tupla3f(0,1,0), Tupla3f(0,1,0));
    // frente, con proyección perspectiva
    p5_camaras.push_back(CamaraInteractiva());
    p5_camaras[2].vf = ViewFrustum(45, 1, 0.5, 10);
    p5_camaras[2].mcv = MarcoCoorVista(Tupla3f(1,1,1), Tupla3f(0,0,0), Tupla3f(0,1,0));
    p5_camara_activa = 0;
}

void P5_DibujarObjetos( unsigned modo ){
    p5_cv.modo_vis = modo;
    p5_obj->visualizar(p5_cv);
}

void P5_FijarMVPOpenGL(){
    p5_camaras[p5_camara_activa].fijarMVPOpenGL();
}

bool P5_FGE_PulsarTeclaNormal(  unsigned char tecla ){
    bool tecla_correcta = false;
    const uint desp = 1;

    switch(tecla){
    case 'C':
        tecla_correcta = true;
        p5_camara_activa += 1;
        p5_camara_activa %= p5_camaras.size();
        break;
    case 'V':
        tecla_correcta = true;
        p5_camaras[p5_camara_activa].examinar = !p5_camaras[p5_camara_activa].examinar;
        break;
    case '+':
        p5_camaras[p5_camara_activa].desplaZ(desp);
        tecla_correcta = true;
        break;
    case '-':
        p5_camaras[p5_camara_activa].desplaZ(-desp);
        tecla_correcta = true;
        break;
    default:
        tecla_correcta = false;
    }

    return tecla_correcta;
}

bool P5_FGE_PulsarTeclaEspecial(  unsigned char tecla ){
    bool tecla_correcta = false;
    const uint desp = 1;

    switch (tecla){
    case GLUT_KEY_LEFT:
        p5_camaras[p5_camara_activa].moverHV(-desp,0);
        tecla_correcta = true;
        break;
    case GLUT_KEY_RIGHT:
        p5_camaras[p5_camara_activa].moverHV(desp,0);
        tecla_correcta = true;
        break;
    case GLUT_KEY_UP:
        p5_camaras[p5_camara_activa].moverHV(0,desp);
        tecla_correcta = true;
        break;
    case GLUT_KEY_DOWN:
        p5_camaras[p5_camara_activa].moverHV(0,-desp);
        tecla_correcta = true;
        break;
    default:
        tecla_correcta = false ;
        break ;
    }

    return tecla_correcta;
}
