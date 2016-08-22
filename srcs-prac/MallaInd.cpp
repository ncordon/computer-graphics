#include "MallaInd.hpp"

void MallaInd::visualizar(ContextoVis &cv){
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

        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, vertices[0]);
        glDrawElements(GL_TRIANGLES, caras.size()*3, GL_UNSIGNED_INT, caras[0]);
        glDisableClientState(GL_VERTEX_ARRAY);
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

        glEnableClientState(GL_VERTEX_ARRAY);
        // Dibuja las caras pares en un color
        glColor3f(0.2, 0.2, 0.2);
        glVertexPointer(3, GL_FLOAT, 0, vertices[0]);
        glDrawElements(GL_TRIANGLES, caras_pares.size()*3, GL_UNSIGNED_INT, caras_pares[0]);
        // Dibuja las caras impares en otro color
        glColor3f(0.8, 0.8, 0.8);
        glVertexPointer(3, GL_FLOAT, 0, vertices[0]);
        glDrawElements(GL_TRIANGLES, caras_impares.size()*3, GL_UNSIGNED_INT, caras_impares[0]);

        glDisableClientState(GL_VERTEX_ARRAY);
    }
    else if (cv.modo_vis==4){
    }
    else if (cv.modo_vis==5){
    }
}


void MallaInd::calcularNormales(){
    std::vector< std::vector<int> > adyacentes_vertices (vertices.size(), std::vector<int>());

    for (int i = 0; i < caras.size(); i++){
        Tupla3f a = vertices[ caras[i](1) ] - vertices[ caras[i](0) ];
        Tupla3f b = vertices[ caras[i](2) ] - vertices[ caras[i](0) ];

        normal_caras.push_back (a.cross(b).normalized());
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

        normal_vertices.push_back(m.normalized());
    }
}
