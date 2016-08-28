#include "MallaInd.hpp"

void MallaInd::visualizar(ContextoVis &cv){
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices[0]);

    if (cv.modo_vis < 3){
        glColor3f(color(R), color(G), color(B));

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

            if (!normal_caras.empty()){
                glEnableClientState(GL_NORMAL_ARRAY);
                glNormalPointer(GL_FLOAT, 0, normal_caras[0]);
            }
        }
        // Modo con iluminación y sombreado de suave
        else if (cv.modo_vis==5){
            glShadeModel(GL_SMOOTH);

            if (!normal_vertices.empty()){
                glEnableClientState(GL_NORMAL_ARRAY);
                glNormalPointer(GL_FLOAT, 0, normal_vertices[0]);
            }
        }

        // Si hay coordenadas de textura...
        if (!textura_coords.empty()){
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glTexCoordPointer( 2, GL_FLOAT, 0, textura_coords[0] );
        }

        glDrawElements(GL_TRIANGLES, caras.size()*3, GL_UNSIGNED_INT, caras[0]);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    }
    glDisableClientState(GL_VERTEX_ARRAY);
}


void MallaInd::calcularNormales(){
    std::vector< std::vector<int> > adyacentes_vertices (vertices.size(), std::vector<int>());

    for (int i = 0; i < caras.size(); i++){
        Tupla3f a = vertices[ caras[i](1) ] - vertices[ caras[i](0) ];
        Tupla3f b = vertices[ caras[i](2) ] - vertices[ caras[i](0) ];

        normal_caras.push_back (normalize(a.cross(b)));
    }

    // Cálculo de las caras adyacentes a cada vector
    for (int i = 0; i < caras.size(); i++){
        for (int j = 0; j < 3; j++)
          adyacentes_vertices[caras[i][j]].push_back(i);
    }

    for (int i = 0; i < vertices.size(); i++){
        Tupla3f m(0,0,0);

        for (int j = 0; j < adyacentes_vertices[i].size(); j++){
            m = m + normal_caras[ adyacentes_vertices[i][j] ];
        }

        normal_vertices.push_back(normalize(m));
    }
}

Tupla3f MallaInd::normalize(Tupla3f m){
    if (m(X) || m(Y) || m(Z))
        return m.normalized();
    else
        return Tupla3f(0,1,0);
}
