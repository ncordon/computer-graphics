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
    // perfil
    p5_camaras.push_back(CamaraInteractiva());
    p5_camaras[1].examinar = true;
    p5_camaras[1].moverHV(M_PI, 0);
    // planta
    p5_camaras.push_back(CamaraInteractiva());
    p5_camaras[2].examinar = true;
    p5_camaras[2].moverHV(0, M_PI);
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
    default:
        tecla_correcta = false;
    }

    return tecla_correcta;
}

bool P5_FGE_PulsarTeclaEspecial(  unsigned char tecla ){
  /*
      Tecla c/C  cambia la camara activa, pasa a la siguiente, o de la última a la primera (se debe imprimir un mensaje indicando cual es la nueva cámara activa). No se usarán para esto las teclas de función (F1,F2,F3) que se indican en el guión.
      Tecla v/V  si la camara activa está en modo examinar, ponerla en modo primera persona. Si la cámara activa está en modo primera persona, no hace nada. En cualquier caso se indica en un mensaje el nuevo modo.
      Flecha izquierda:
      desplazar o rotar la cámara activa en horizontal, hacia la izquierda.
      Flecha derecha:
      desplazar o rotar la cámara activa en horizontal, hacia la derecha.
      Flecha arriba:
      desplazar o rotar la cámara en vértical, hacia arriba.
      Flecha abajo:
      desplazar o rotar la cámara en vértical, hacia abajo.
      Tecla + (o página arriba):
      desplazar la camara en la direción de la vista (eje Z de la cámara), hacia adelante.
      Tecla - (o página abajo):
      desplazar la cámara en la direccion de la vista (eje Z de la cámara), hacia detrás.
  */
}
