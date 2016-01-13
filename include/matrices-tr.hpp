// *********************************************************************
// **
// ** Gestión de matrices 4x4 de transformacion (declaraciones)
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


#ifndef MATRICES_TR_HPP
#define MATRICES_TR_HPP

#include "matrizg.hpp"

// ---------------------------------------------------------------------
// creación y operadores de matrices: transformaciones de modelado

Matriz4f MAT_Ident( ) ;
Matriz4f MAT_Traslacion( const float d[3] ) ;
Matriz4f MAT_Traslacion( const float dx, const float dy , const float dz ) ;

Matriz4f MAT_Escalado( const float sx, const float sy, const float sz ) ;
Matriz4f MAT_Rotacion( const float ang_gra, const float ex, const float ey, const float ez ) ;
Matriz4f MAT_Filas( const Tupla3f & fila0, const Tupla3f & fila1, const Tupla3f & fila2 );  

// ---------------------------------------------------------------------
// matrices para la transformacion de vista:

Matriz4f MAT_LookAt( const float origen[3], const float centro[3], const float vup[3] );  

// ---------------------------------------------------------------------
// matrices para la transf. de proyección

Matriz4f MAT_Frustum( const float l, const float r, const float b, const float t, const float n, const float f );
Matriz4f MAT_Ortografica( const float l, const float r, const float b, const float t, const float n, const float f );
Matriz4f MAT_Perspectiva( const float fovy_grad, const float raz_asp, const float n, const float f );

#endif
