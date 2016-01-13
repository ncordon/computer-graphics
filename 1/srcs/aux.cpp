// *********************************************************************
// **
// ** Rutinas auxiliares:
// ** - Gestión de errores en general
// ** - Comprobación de errores de OpenGL (implementacion)
// ** - Inicialización de glew, 
// ** - Comprobacion de la versión de OpenGL
// **
// ** Copyright (C) 2014 Carlos Ureña
// **
// ** This program is free software: you can redistribute it and/or modify
// ** it under the terms of the GNU General Public License as published by
// ** the Free Software Foundation, either version 3 of the License, or
// ** (at your option) any later version.
// **
// ** This program is distributed in the hope that it will be useful,
// ** but WITHOUT ANY WARRANTY; without even the implied warranty of
// ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// ** GNU General Public License for more details.
// **
// ** You should have received a copy of the GNU General Public License
// ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
// **
// *********************************************************************



#include "aux.hpp"


// *********************************************************************
// gestion de errores
   
void GestionarError( const char * msg, const char * nomArchivo, int linea )
{
   std::cout
         << std::endl
         << "-----------------------------------------------------------" << std::endl
         << "Error detectado:" << std::endl
         << "   descripción : " << msg  << "." << std::endl
         << "   archivo     : " << nomArchivo << std::endl  
         << "   línea       : " << linea << std::endl
         << "-----------------------------------------------------------" << std::endl
         << "programa abortado." << std:: endl
         << std::flush ;
         
    exit(1) ;
}

// -----------------------------------------------------------------------------
// códigos y descripciones de errores detectado por 'glGetError'

const unsigned numErrors = 6 ;


const GLenum errCodes[numErrors] =
{
   GL_NO_ERROR ,
   GL_INVALID_ENUM ,
   GL_INVALID_VALUE ,
   GL_INVALID_OPERATION ,
   GL_INVALID_FRAMEBUFFER_OPERATION ,
   GL_OUT_OF_MEMORY
} ;

const char * errDescr[numErrors] =
{
   "Error when trying to report an error: no error has been recorded",
   "An unacceptable value is specified for an enumerated argument",
   "A numeric argument is out of range",
   "The specified operation is not allowed in the current state",
   "The command is trying to render to or read from the framebuffer while the currently bound framebuffer is not framebuffer complete (i.e. the return value from glCheckFramebufferStatus is not GL_FRAMEBUFFER_COMPLETE)",
   "There is not enough memory left to execute the command"
} ;


const char * errCodeString[numErrors] =
{
   "GL_NO_ERROR",
   "GL_INVALID_ENUM",
   "GL_INVALID_VALUE",
   "GL_INVALID_OPERATION",
   "GL_INVALID_FRAMEBUFFER_OPERATION",
   "GL_OUT_OF_MEMORY"
} ;

// ---------------------------------------------------------------------
// devuelve descripción de error dado el código de error opengl

std::string ErrorDescr( GLenum errorCode )
{
   int iErr = -1 ;
   for ( unsigned i = 0 ; i < numErrors ; i++ )
   {  if ( errCodes[i] == errorCode)
      {  iErr = i ;
         break ;
      }
   }
   if ( iErr == -1 )
      return std::string("Error when trying to report an error: error code is not a valid error code for 'glGetError'") ;
   return std::string( errDescr[iErr] ) ;
}

std::string ErrorCodeString( GLenum errorCode )
{
   int iErr = -1 ;
   for ( unsigned i = 0 ; i < numErrors ; i++ )
   {  if ( errCodes[i] == errorCode)
      {  iErr = i ;
         break ;
      }
   }
   if ( iErr == -1 )
      return std::string("** invalid error code **") ;
   return std::string( errCodeString[iErr] ) ;
}

//----------------------------------------------------------------------

void CompruebaErrorOpenGL( const char * nomArchivo, int linea )
{
   const GLint codigoError = glGetError() ;
   
   if ( codigoError != GL_NO_ERROR )
   {  std::cout 
         << std::endl
         << "Detectado error de OpenGL. Programa abortado." << std::endl 
         
         << "   archivo (linea) : " << QuitarPath(nomArchivo) << " (" << linea << ")" << std::endl 
       //<< "   descripción     : " << gluErrorString(codigoError)  << "." << std::endl
         << "   código error    : " << ErrorCodeString( codigoError )  << std::endl
         << "   descripción     : " << ErrorDescr( codigoError )  << "." << std::endl
         << std::endl << std::flush ;
      exit(1);
   }
}

//----------------------------------------------------------------------

void CalculaVersion(  const char *str, int & major, int & minor )
{
   // podría hacerse así, pero las primeras versiones (1.5-) al parecer no tienen GL_MAJOR_VERSION.... :-(
      // glGetIntegerv( GL_MAJOR_VERSION, &major ) ;
      // glGetIntegerv( GL_MINOR_VERSION, &minor ) ;
      
   using namespace std ;
   const 
      std::string ver(str) ;
   size_t //auto
      blanco = ver.find_first_of(' ') ;
   if ( blanco == string::npos ) 
      blanco = ver.length() ;
   
   const size_t //auto
      punto = ver.find_first_of('.') ;
   assert( punto != string::npos ); // salta si no encuentra el punto
   assert( punto+1 < blanco );
   
   const string 
      smajor = ver.substr( 0, punto ),
      sminor = ver.substr( punto+1, blanco-punto-1 );
   
   major = atoi(smajor.c_str());
   minor = atoi(sminor.c_str()); 
}

// ---------------------------------------------------------------------
// quita el path de un nombre de archivo con path

std::string QuitarPath( const std::string & path_arch )
{
   //const size_t
   
   const size_t // auto
   	barra = path_arch.find_last_of('/') ;
   if ( barra == std::string::npos ) // no tiene '/' (devolver tal cual)
      return path_arch ;
   else
      return path_arch.substr( barra+1 );
   
}

// ---------------------------------------------------------------------
// devuelve true si se soporta al menos una versión de OpenGL, se 
// proporciona el número de version dividido en "major" y "minor"

bool SoportaGL( const int min_major, const int min_minor ) 
{
   static GLint major,minor ;
   static bool primera = true ;
   
   if ( primera )
   {  
      // parser de la cadena (GL_VERSION) 
      using namespace std ;
      CalculaVersion( (const char *) glGetString(GL_VERSION), major, minor ) ;
      cout << "calculada version de OpenGL: " << major << "." << minor << " (" << glGetString(GL_VERSION) << ")" << endl << flush ;
      primera = false ;
   }
   
   if ( min_major < major )
      return true;
   if ( min_major == major )
      if ( min_minor <= minor )
         return true;
   return false ;
}


// ---------------------------------------------------------------------

bool SoportaGLSL( const int min_major, const int min_minor )
{
   static GLint major,minor ;
   static bool primera = true ;
   
   if ( primera )
   {
      // parser de la cadena (GL_VERSION)
      using namespace std ;
      CalculaVersion( (const char *) glGetString(GL_SHADING_LANGUAGE_VERSION), major, minor ) ;
      cout << "calculada version de GLSL: " << major << "." << minor << " (" << glGetString(GL_SHADING_LANGUAGE_VERSION) << ")" << endl << flush ;
      primera = false ;
   }
   
   if ( min_major < major )
      return true;
   if ( min_major == major )
      if ( min_minor <= minor )
         return true;
   return false ;
}


//----------------------------------------------------------------------

void ExigirGLEW( const char * msg )
{
   static bool primera = true ;

   if ( ! primera )
      return ;
   primera = false ;
   
   using namespace std ;
#ifndef GLEW_OK
   cout << "no se han incluido los headers de GLEW" << endl ;
   Error(msg) ;
#else
   GLenum codigoError = glewInit();
   if ( codigoError != GLEW_OK ) // comprobar posibles errores
   {  cout << "Imposible inicializar ’GLEW’, mensaje recibido: "
             << glewGetErrorString(codigoError) << endl ;
      Error(msg) ;
   }
   else
      cout << "librería GLEW inicializada correctamente." << endl << flush ;
#endif
}

//----------------------------------------------------------------------

void ExigirVersionGL( const int min_major, const int min_minor, const char * msg ) 
{
   if ( 2 <= min_major )
      ExigirGLEW( msg ) ;
      
   if ( SoportaGL( min_major, min_minor ) )
      return ;
   
   using namespace std ;
   cout << "Se exige al menos la versión de OpenGL : " << min_major << "." << min_minor << endl   
        << "Se ha encontrado la versión de OpenGL  : " << glGetString(GL_VERSION)  << endl ;
   Error(msg);
}

// ---------------------------------------------------------------------

void InformeOpenGL(  )
{
   GLint acc_r, acc_g, acc_b ;
   glGetIntegerv( GL_ACCUM_RED_BITS,   &acc_r );
   glGetIntegerv( GL_ACCUM_GREEN_BITS, &acc_g );
   glGetIntegerv( GL_ACCUM_BLUE_BITS,  &acc_b );
   
   using namespace std ;
   cout  << "datos de versión e implementación de OpenGL" << endl
         << "    implementación de   == " << glGetString(GL_VENDOR)  << endl 
         << "    hardware            == " << glGetString(GL_RENDERER) << endl 
         << "    version de OpenGL   == " << glGetString(GL_VERSION) << endl 
         << "    version de GLSL     == " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl 
         << "    bits buff.accum     == " << "(" << acc_r << "," << acc_g << "," << acc_b << ")" << endl
         << flush ;
}

//----------------------------------------------------------------------

void CrearVentanaGLUT( const char * titulo, const  float fr_alto )
{
   using namespace std ;
   
   cout << "voy a crear ventana glut (0)....." << endl << flush ;
   // calcular posición y tamaño de la ventana
   const int 
      pan_tam_x = glutGet( GLUT_SCREEN_WIDTH ),
      pan_tam_y = glutGet( GLUT_SCREEN_HEIGHT ) ;
   int 
      ven_pos_x = 64 ,  ven_tam_x = 512 ,
      ven_pos_y = 64 ,  ven_tam_y = 512 ;

   if ( pan_tam_x > 0 && pan_tam_y > 0 )
   {
      ven_tam_y = int( fr_alto*pan_tam_y ) ;
      ven_tam_x = ven_tam_y ;
      ven_pos_x = (pan_tam_x - ven_tam_x)/2 ;
      ven_pos_y = (pan_tam_y - ven_tam_y)/2 ;
   }
   else
      cout << "advertencia: no se ha podido leer tamaño de la pantalla" << endl << flush ;
   
   cout << "voy a crear ventana glut (1)....." << endl << flush ;
   
   // fijar parámetros de la ventana: planos, posición y tamaño:
   glutInitDisplayMode( GLUT_DOUBLE | GLUT_DEPTH | GLUT_ACCUM ); // planos: buffer doble, z-buffer, buffer de acumulación
   glutInitWindowPosition( ven_pos_x, ven_pos_y );   // posicion inicial
   glutInitWindowSize( ven_tam_x, ven_tam_y );            // tamaño inicial
   cout << "voy a crear ventana glut (2)....." << endl << flush ;
   
   // crear la ventana, indicando el titulo
   glutCreateWindow( titulo );
   
   using namespace std ;
   cout << "creada ventana glut, ancho == " << ven_tam_x << ", alto == " << ven_tam_y << endl ;
}





   

   
   




