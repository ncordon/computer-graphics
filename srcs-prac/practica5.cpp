#include "practica5.hpp"

static NodoGrafoEscena *p5_obj;
static ContextoVis p5_cv;
static vector< CamaraInteractiva > p5_camaras;
static int p5_camara_activa;
static int xant, yant;
enum estado{MOVIENDO_CAMARA_FIRSTPERSON, OTHER};
static estado estadoRaton;

void P5_Inicializar( int argc, char *argv[] ){
    p5_obj = new NodoGrafoEscena;

    p5_obj->agregar(new Lata, true);
    p5_obj->agregar(MAT_Escalado(0.2,0.2,0.2));
    // Valor 1.4 tomado del peon.ply
    p5_obj->agregar(MAT_Traslacion(1,1.4,3));
    p5_obj->agregar(new PeonMadera, true);
    p5_obj->agregar(MAT_Traslacion(2.2,0,0));
    p5_obj->agregar(new PeonBlanco, true);
    p5_obj->agregar(MAT_Traslacion(2.2,0,0));
    p5_obj->agregar(new PeonNegro, true);


    // alzado
    p5_camaras.push_back(CamaraInteractiva());
    p5_camaras[0].mcv = MarcoCoorVista(Tupla3f(0.5,1,1), Tupla3f(0.5,1,0), Tupla3f(0,1,0));
    // perfil, con proyección ortográfica
    p5_camaras.push_back(CamaraInteractiva());
    p5_camaras[1].mcv = MarcoCoorVista(Tupla3f(-1,1,0), Tupla3f(0,1,0), Tupla3f(0,1,0));
    // frente, con proyección perspectiva
    p5_camaras.push_back(CamaraInteractiva());
    p5_camaras[2].vf = ViewFrustum(45, 1, 0.5, 10);
    p5_camaras[2].mcv = MarcoCoorVista(Tupla3f(2,2,2), Tupla3f(0,0,0), Tupla3f(0,1,0));
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

void P5_FGE_ClickRaton( int button, int state, int x, int y ){
    if (button == GLUT_RIGHT_BUTTON){
        if (state == GLUT_DOWN){
            // Se pulsa el botón, por lo que se entra en el estado "moviendo cámara"
            estadoRaton = MOVIENDO_CAMARA_FIRSTPERSON;
            xant = x;
            yant = y;
        }
        else{
            // Se levanta el botón, por lo que se sale del estado "moviendo cámara"
            estadoRaton = OTHER;
        }
    }
    else if(button == GLUT_LEFT_BUTTON){
        if(state == GLUT_DOWN){
            estadoRaton = OTHER;
            GLubyte pixels[3];
            NodoGrafoEscena *obj;
            glDisable(GL_LIGHTING);
            glDisable(GL_TEXTURE_2D);
            glDisable(GL_DITHER);
            glShadeModel(GL_FLAT);
            glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glColor3ub(0,0,0);
            p5_obj->modoSeleccion();

            glReadPixels(x, (glutGet( GLUT_WINDOW_HEIGHT ) - y), 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixels);
            //cerr << "x " << x << endl;
            //cerr << "y " << y << endl;
            //cerr << (int) pixels[0] << endl;

            obj = p5_obj->buscarNodoConIdent(pixels[0]);

            if(obj != NULL){
                cout << "Centrando imagen sobre " << obj->nombre() << endl;
                p5_camaras[p5_camara_activa].fijarAten( obj->centro );
            }
            else
                cout << "Ningún nodo seleccionado" << endl;

            glEnable(GL_DITHER);
        }
        glutPostRedisplay();
    }
}

void P5_FGE_RatonMovido( int x, int y ){
    if ( estadoRaton==MOVIENDO_CAMARA_FIRSTPERSON ){
        int dx = x-xant;
        int dy = y-yant;

        p5_camaras[p5_camara_activa].moverHV(dx, dy);

        xant = x;
        yant = y;
    }
}
