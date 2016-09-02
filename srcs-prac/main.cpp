// *********************************************************************
// ** ** Informática Gráfica, curso 2014-15 ** Carlos Ureña Almagro **
// ** Función 'main', inicialización y gestores de eventos
// ** *********************************************************************

// includes de C/C++

#include <cctype>   // toupper
#include <string>   // std::string
#include <iostream> // std::cout
#include <fstream>  // ifstream
#include <cmath>    // fabs

// includes en ../include
#include "aux.hpp"  // include cabeceras de opengl / glut / glut / glew

// includes de archivos en el directorio de trabajo (de las prácticas)
#include "practica1.hpp"
#include "practica2.hpp"
#include "practica3.hpp"
#include "practica4.hpp"
#include "practica5.hpp"

// evita la necesidad de escribir std::
using namespace std ;

// Número de prácticas
const unsigned N_PRACTICAS = 5;

// Número de modos de visualización
const unsigned N_MODOS_VIS = 6;
// *********************************************************************
// **
// ** Variables globales
// ** (se inicializan en las funciones de inicialización)
// **
// *********************************************************************

// variables que definen la posicion de la camara en coordenadas polares

float
    camara_angulo_x ,   // angulo de rotación entorno al eje X
    camara_angulo_y ;   // angulo de rotación entorno al eje Y

// ---------------------------------------------------------------------
// variables que definen el view-frustum (zona visible del mundo)

float
    frustum_factor_escala ,  // factor de escala homogeneo que se aplica al frustum (sirve para alejar o acercar)
    frustum_ancho ,          // ancho, en coordenadas del mundo
    frustum_dis_del ,        // distancia al plano de recorte delantero (near)
    frustum_dis_tra ;        // distancia al plano de recorte trasero (far)

// ---------------------------------------------------------------------
// variables que determinan la posicion y tamaño inicial de la ventana
// (el tamaño se actualiza al cambiar el tamaño durante la ejecución)

int
    ventana_pos_x  ,  // posicion (X) inicial de la ventana, en pixels
    ventana_pos_y  ,  // posicion (Y) inicial de la ventana, en pixels
    ventana_tam_x  ,  // ancho inicial y actual de la ventana, en pixels
    ventana_tam_y  ;  // alto inicial actual de la ventana, en pixels

// ---------------------------------------------------------------------

unsigned
    modo_vis  ,  // modo de visualización (0,1,3,4)
    practica_actual ;  // practica actual (cambiable por teclado) (1,2,3,4,5)

// *********************************************************************
// **
// ** Funciones auxiliares:
// **
// *********************************************************************


// fija la transformación de proyeccion (zona visible del mundo == frustum)

void FijarProyeccion()
{
    const GLfloat ratioYX = GLfloat( ventana_tam_y )/GLfloat( ventana_tam_x );

    CError();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // (3) proyectar en el plano de visión
    glFrustum
        (  -frustum_ancho,
           +frustum_ancho,
           -frustum_ancho*ratioYX,
           +frustum_ancho*ratioYX,
           +frustum_dis_del,
           +frustum_dis_tra
           );


    // (2) situar el origen (0,0,0), en mitad del view frustum
    //     (en la rama negativa del eje Z)
    glTranslatef( 0.0,0.0,-0.5*(frustum_dis_del+frustum_dis_tra));

    // (1) aplicar factor de escala
    glScalef( frustum_factor_escala, frustum_factor_escala,  frustum_factor_escala );

    CError();
}


// ---------------------------------------------------------------------
// fijar viewport y proyección (viewport ocupa toda la ventana)

void FijarViewportProyeccion()
{
    glViewport( 0, 0, ventana_tam_x, ventana_tam_y );
    FijarProyeccion() ;
}

// ---------------------------------------------------------------------
// fija la transformación de vista (posiciona la camara)

void FijarCamara()
{
    CError();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(camara_angulo_x,1,0,0);
    glRotatef(camara_angulo_y,0,1,0);

    CError();
}

// ---------------------------------------------------------------------
// dibuja los ejes utilizando la primitiva grafica de lineas

void DibujarEjes()
{
    const float long_ejes = 30.0 ;

    // establecer modo de dibujo a lineas (podría estar en puntos)
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    // dibujar tres segmentos
    glBegin(GL_LINES);
    // eje X, color rojo
    glColor3f( 1.0, 0.0, 0.0 );
    glVertex3f( -long_ejes, 0.0, 0.0 );
    glVertex3f( +long_ejes, 0.0, 0.0 );
    // eje Y, color verde
    glColor3f( 0.0, 1.0, 0.0 );
    glVertex3f( 0.0, -long_ejes, 0.0 );
    glVertex3f( 0.0, +long_ejes, 0.0 );
    // eje Z, color azul
    glColor3f( 0.0, 0.0, 1.0 );
    glVertex3f( 0.0, 0.0, -long_ejes );
    glVertex3f( 0.0, 0.0, +long_ejes );
    glEnd();

    // bola en el origen, negra
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    glColor3f(0.0,0.0,0.0);
    glutSolidSphere(0.01,8,8);

}

// ---------------------------------------------------------------------
// asigna el color de fondo actual a todos los pixels de la ventana

void LimpiarVentana()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

// ---------------------------------------------------------------------
// dibuja los objetos de la escena

void DibujarObjetos()
{
    switch(practica_actual){
    case 1 :
        P1_DibujarObjetos(modo_vis) ; // definido en 'practica1.hpp'
        break ;
    case 2 :
        P2_DibujarObjetos(modo_vis) ; // definido en 'practica2.hpp'
        break ;
    case 3 :
        P3_DibujarObjetos(modo_vis) ; // definido en 'practica3.hpp'
        break ;
    case 4 :
        P4_DibujarObjetos(modo_vis) ; // definido en 'practica4.hpp'
        break ;
    case 5 :
        P5_DibujarObjetos(modo_vis) ; // definido en 'practica5.hpp'
        break ;
    default :
        cout << "El valor de 'practica_actual' (" << practica_actual  << ") es incorrecto" << endl ;
        break ;
    }
}


// *********************************************************************
// **
// ** Funciones gestoras de eventos
// **
// *********************************************************************

// F.G. del evento de redibujado (se produce cuando hay que volver a
// dibujar la ventana, tipicamente tras producirse otros eventos)

void FGE_Redibujado()
{
    using namespace std ;
    //cout << "redibujado......" << endl << flush ;
    if (practica_actual != 5){
        FijarViewportProyeccion() ; // necesario pues la escala puede cambiar
        FijarCamara();
    }
    else{
      glViewport( 0,0,ventana_tam_x,ventana_tam_y );// fijar viewport (igual que en el resto de prácticas)
      P5_FijarMVPOpenGL() ;                         // fijar proyección y vista OpenGL usando cámara activa de la práctica 5
    }
    LimpiarVentana();
    DibujarEjes() ;
    DibujarObjetos();
    glutSwapBuffers();
}

// ---------------------------------------------------------------------
// F.G. del evento de cambio de tamaño de la ventana

void FGE_CambioTamano( int nuevoAncho, int nuevoAlto )
{
    // guardar nuevo tamaño de la ventana
    ventana_tam_x  = nuevoAncho;
    ventana_tam_y  = nuevoAlto ;

    // reestablecer frustum, viewport y proyección
    FijarViewportProyeccion();

    // forzar un nuevo evento de redibujado, para actualizar ventana
    glutPostRedisplay();
}

// ---------------------------------------------------------------------
// F.G. del evento de pulsación de la tecla normal
//
// parámetros:
//       tecla: carácter corresondiente a la tecla (minúscula)
//       x_raton, y_raton : posición del ratón al pulsar

void FGE_PulsarTeclaNormal( unsigned char tecla, int x_raton, int y_raton )
{
    // true si al acabar de procesar el evento resulta que es necesario redibujar

    bool redibujar = true ;
    tecla = toupper(tecla);

    switch (tecla){
    case 'M' :
        modo_vis += 1;
        modo_vis %= N_MODOS_VIS;
        break;
    case 'Q' :
        exit( 0 );
        break ;
    case '+' :
        frustum_factor_escala *= 1.05;
        break;
    case '-' :
        frustum_factor_escala /= 1.05;
        break;
    case 'P':
        // Cambiar cuando lleguemos a 4 prácticas
        practica_actual %= N_PRACTICAS;
        practica_actual += 1;
        break;
    default:
        redibujar = false ;
        switch( practica_actual ) {
        case 1:
            redibujar = P1_FGE_PulsarTeclaNormal(tecla) ; // true si es necesario redibujar
            break;
        case 2:
            redibujar = P2_FGE_PulsarTeclaNormal(tecla);
            break;
        case 3:
            redibujar = P3_FGE_PulsarTeclaNormal(tecla);
            break;
        case 4:
            redibujar = P4_FGE_PulsarTeclaNormal(tecla);
            break;
        case 5:
            redibujar = P5_FGE_PulsarTeclaNormal(tecla);
            break;
        default :
            redibujar = false ; // la tecla no es de la práctica activa (no es necesario redibujar)
        }
        break ;
    }
    using namespace std ;
    //cout << "tecla normal....." << frustum_factor_escala << endl ;

    // si se ha cambiado algo, forzar evento de redibujado
    if (redibujar)
        glutPostRedisplay();
}

// ---------------------------------------------------------------------
// F.G. del evento de pulsación de la tecla especial
//
// parámetros:
//       tecla: código GLUT de la tecla pulsada
//       x_raton, y_raton : posición del ratón al pulsar


void FGE_PulsarTeclaEspecial( int tecla, int x_raton, int y_raton )
{
    bool redisp = true ;
    const float da = 5.0 ; // incremento en grados de ángulos de camara

    switch ( tecla )
        {
        case GLUT_KEY_LEFT:
            camara_angulo_y = camara_angulo_y - da ;
            break;
        case GLUT_KEY_RIGHT:
            camara_angulo_y = camara_angulo_y + da ;
            break;
        case GLUT_KEY_UP:
            camara_angulo_x = camara_angulo_x - da ;
            break;
        case GLUT_KEY_DOWN:
            camara_angulo_x = camara_angulo_x + da ;
            break;
        case GLUT_KEY_PAGE_UP:
            frustum_factor_escala *= 1.05;
            break;
        case GLUT_KEY_PAGE_DOWN:
            frustum_factor_escala /= 1.05;
            break;
        default:
            redisp = false ;
            break ;
	}
    using namespace std ;

    // si se ha cambiado algo, forzar evento de redibujado
    if ( redisp )
        glutPostRedisplay();
}

// *********************************************************************
// **
// ** Funciones de inicialización
// **
// *********************************************************************

// inicialización de GLUT: creación de la ventana, designar FGEs

void Inicializa_GLUT( int argc, char * argv[] )
{

    // inicializa variables globales usadas en esta función (y otras)
    ventana_pos_x  = 50 ;
    ventana_pos_y  = 50  ;
    ventana_tam_x  = 800 ;  // ancho inicial y actual de la ventana, en pixels
    ventana_tam_y  = 800 ;  // alto inicial actual de la ventana, en pixels

    // inicializa glut:
    glutInit( &argc, argv );

    // establece posicion inicial de la ventana:
    glutInitWindowPosition( ventana_pos_x, ventana_pos_y );

    // establece tamaño inicial de la ventana:
    glutInitWindowSize( ventana_tam_x, ventana_tam_y );

    // establece atributos o tipo de ventana:
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );

    // crea y visualiza una ventana:
    glutCreateWindow("Practicas IG GIM (15-16)");

    // establece función gestora del evento de redibujado:
    glutDisplayFunc( FGE_Redibujado );

    // establece función gestora del evento de cambio de tamaño:
    glutReshapeFunc( FGE_CambioTamano );

    // establece función gestora del evento de pulsación de tecla normal:
    glutKeyboardFunc( FGE_PulsarTeclaNormal );

    // establece función gestora del evento de pulsación de tecla especial:
    glutSpecialFunc( FGE_PulsarTeclaEspecial );
}

// ---------------------------------------------------------------------
// Inicialización de las variables globales del programa

void Inicializa_Vars( ){
    // inicializar parámetros del frustum
    frustum_dis_del         = 0.1 ;
    frustum_dis_tra         = 10.0;
    frustum_ancho           = 0.5*frustum_dis_del ;
    frustum_factor_escala   = 2.0 ;

    // inicializar parámetros de la cámara
    camara_angulo_x = 0.0 ;
    camara_angulo_y = 0.0 ;

    // inicializar práctica actual y modo de visualización inicial
    practica_actual = N_PRACTICAS ;
    modo_vis = 0 ;
}

// ---------------------------------------------------------------------
// inicialización de OpenGL

void Inicializa_OpenGL( ){
    // borrar posibles errores anteriores
    CError();

    // habilitar test de comparación de profundidades para 3D (y 2D)
    // es necesario, no está habilitado por defecto:
    // https://www.opengl.org/wiki/Depth_Buffer
    glEnable( GL_DEPTH_TEST );

    // establecer color de fondo: (1,1,1) (blanco)
    glClearColor( 1.0, 1.0, 1.0, 1.0 ) ;

    // establecer color inicial para todas las primitivas
    glColor3f( 0.7, 0.2, 0.4 ) ;

    // establecer ancho de línea
    glLineWidth( 1.0 );

    // establecer tamaño de los puntos
    glPointSize( 5.0 );

    // establecer modo de visualización de prim.
    // (las tres posibilidades son: GL_POINT, GL_LINE, GL_FILL)
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    // establecer la cámara, la proyección y el viewport
    FijarViewportProyeccion() ;
    FijarCamara() ;

    // imprimir datos del hardware y la implementación de OpenGL
    using namespace std ;
    cout  << "Datos de versión e implementación de OpenGL" << endl
          << "  implementación de : " << glGetString(GL_VENDOR)  << endl
          << "  hardware          : " << glGetString(GL_RENDERER) << endl
          << "  version de OpenGL : " << glGetString(GL_VERSION) << endl
          << "  version de GLSL   : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl
          << flush ;

    // ya está
    CError();
}

// ---------------------------------------------------------------------
// Código de inicialización (llama a los dos anteriores, entre otros)

void Inicializar( int argc, char *argv[] ){
    // inicializa las variables del programa
    Inicializa_Vars() ;

    // glut (crea la ventana)
    Inicializa_GLUT( argc, argv ) ;

    // opengl: define proyección y atributos iniciales
    Inicializa_OpenGL() ;

    // inicializar práctica 1.
    P1_Inicializar( argc, argv ) ;

    // inicializar práctica 2.
    P2_Inicializar( argc, argv ) ;

    // inicializar práctica 3.
    P3_Inicializar( argc, argv ) ;

    // inicializar práctica 4.
    P4_Inicializar( argc, argv ) ;

    // inicializar práctica 5.
    P5_Inicializar( argc, argv ) ;
}

// *********************************************************************
// **
// ** Función principal
// **
// *********************************************************************


int main( int argc, char *argv[] ){
    // incializar el programa
    Inicializar( argc, argv ) ;

    // llamar al bucle de gestión de eventos de glut, tiene el
    // control hasta el final de la aplicación
    glutMainLoop();

    // ya está
    return 0;
}
