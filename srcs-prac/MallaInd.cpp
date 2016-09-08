#include "MallaInd.hpp"

void MallaInd::visualizar(ContextoVis &cv){
    if (cv.modo_vis < 3){
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, vertices[0]);

//        glColor3f(color(R), color(G), color(B));

        switch(cv.modo_vis){
        case(0):
            // Modo puntos
            glPolygonMode (GL_FRONT_AND_BACK, GL_POINT);
            break;
        case(1):
            // Modo alambre
            glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
            break;
        case(2):
            // Modo sólido
            glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
            break;
        }
        glDrawElements(GL_TRIANGLES, caras.size()*3, GL_UNSIGNED_INT, caras[0]);
    }
    // Modo ajedrez
    else if (cv.modo_vis==3){
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, vertices[0]);

        glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
        std::vector<Tupla3i> caras_pares;
        std::vector<Tupla3i> caras_impares;

        for(uint i=0; i<caras.size(); i++)
            if(i%2==0)
                caras_pares.push_back(caras[i]);
            else
                caras_impares.push_back(caras[i]);

        // Dibuja las caras pares en un color
        glColor3f(0.2, 0.2, 0.2);
        glDrawElements(GL_TRIANGLES, caras_pares.size()*3, GL_UNSIGNED_INT, caras_pares[0]);
        // Dibuja las caras impares en otro color
        glColor3f(0.8, 0.8, 0.8);
        glDrawElements(GL_TRIANGLES, caras_impares.size()*3, GL_UNSIGNED_INT, caras_impares[0]);
    }
    else{
        glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);

        // Modo con iluminación y sombreado plano
        if (cv.modo_vis==4){
            glShadeModel(GL_FLAT);
            glBegin(GL_TRIANGLES);

            for (int i=0; i < caras.size(); i++){
                if (!normal_caras.empty()){
                    Tupla3f m = normal_caras[i];
                    glNormal3f( m(X), m(Y), m(Z) );
                }
                for (int j=0; j < 3; j++){
                    Tupla3f v = vertices[ caras[i][j] ];

                    if (!textura_coords.empty()){
                        Tupla2f t = textura_coords[ caras[i][j] ];
                        glTexCoord2f( t(X),t(Y) );
                    }

                    glVertex3f( v(X),v(Y),v(Z) );
                }
            }

            glEnd();

        }
        // Modo con iluminación y sombreado de suave
        else if (cv.modo_vis==5){
            glShadeModel(GL_SMOOTH);
            glEnableClientState(GL_VERTEX_ARRAY);
            glVertexPointer(3, GL_FLOAT, 0, vertices[0]);

            if (!normal_vertices.empty()){
                glEnableClientState(GL_NORMAL_ARRAY);
                glNormalPointer(GL_FLOAT, 0, normal_vertices[0]);
            }

            // Si hay coordenadas de textura...
            if (!textura_coords.empty()){
                glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                glTexCoordPointer( 2, GL_FLOAT, 0, textura_coords[0] );
            }

            glDrawElements(GL_TRIANGLES, caras.size()*3, GL_UNSIGNED_INT, caras[0]);
        }
    }
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}


void MallaInd::calcularNormales(){
    normal_vertices = std::vector< Tupla3f > (vertices.size(), Tupla3f(0,0,0));

    for (int i = 0; i < caras.size(); i++){
        Tupla3f a = vertices[ caras[i](1) ] - vertices[ caras[i](0) ];
        Tupla3f b = vertices[ caras[i](2) ] - vertices[ caras[i](0) ];
        Tupla3f normal = normalize(a.cross(b));
        normal_caras.push_back (normal);

        for (int j = 0; j < 3; j++)
            normal_vertices[caras[i][j]] = normal_vertices[caras[i][j]] + normal;
    }

    for (int i = 0; i < vertices.size(); i++){
        normal_vertices[i] = normalize(normal_vertices[i]);
    }
}

Tupla3f MallaInd::normalize(Tupla3f m){
    if (m(X) || m(Y) || m(Z))
        return m.normalized();
    else
        return Tupla3f(0,0,1);
}
