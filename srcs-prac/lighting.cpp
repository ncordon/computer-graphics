#include "lighting.hpp"

void MaterialEstandar::activar(){
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, color[0]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color[1]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color[2]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color[3]);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, exponente);

    if(text == NULL)
        glDisable( GL_TEXTURE_2D );
    else
        text->activar();
}


Textura::Textura( const std::string & archivoJPG ){
    img = new jpg::Imagen(archivoJPG);

}

void Textura::activar(){
    glEnable( GL_TEXTURE_2D );


    glGenTextures(1, &id_text);

    switch(mgct){
        case 1:
            glTexGenfv(GL_S, GL_OBJECT_PLANE, cs);
            glTexGenfv(GL_T, GL_OBJECT_PLANE, cs);
            break;
        case 2:
            glTexGenfv(GL_S, GL_EYE_PLANE, cs);
            glTexGenfv(GL_T, GL_EYE_PLANE, cs);
            break;

        default:
            gluBuild2DMipmaps(
                GL_TEXTURE_2D, GL_RGB, img->tamX(), img->tamY(),
                GL_RGB, GL_UNSIGNED_BYTE, (void*)img
            );
            break;
    }

}


FuenteDireccional::FuenteDireccional( float alpha_inicial, float beta_inicial ){
    long_rot = alpha_inicial;
    lat_rot = beta_inicial;
    direccional = true;
}

void FuenteDireccional::variarAngulo( int i, unsigned angulo, float incremento){
    if (angulo == 0)
        long_rot += incremento;
    if (angulo == 1)
        lat_rot += incremento;

    activar(i);
}


void FuenteLuz::activar(int i){
    // Fuente de luz direccional
    if (direccional){
        glMatrixMode( GL_MODELVIEW );
        const float ejeZ[4] = {0.0, 0.0, 1.0, 0.0};

        glPushMatrix();

        glLoadIdentity();
        glRotatef( long_rot, 0.0, 1.0, 0.0);
        glRotatef( lat_rot, -1.0, 0.0, 0.0);
        glLightfv( GL_LIGHT0 + i, GL_POSITION, ejeZ);

        glPopMatrix();
    }
    // Fuente de luz posicional
    else{
        glLightfv( GL_LIGHT0 + i, GL_POSITION, posvec);
    }

    glLightfv(GL_LIGHT0+i, GL_AMBIENT, colores[0]);
    glLightfv(GL_LIGHT0+i, GL_DIFFUSE, colores[1]);
    glLightfv(GL_LIGHT0+i, GL_SPECULAR, colores[2]);
    glEnable (GL_LIGHT0+i);
}

FuentePosicional::FuentePosicional( const Tupla3f & posicion ){
    posvec[0] = posicion(X);
    posvec[1] = posicion(Y);
    posvec[2] = posicion(Z);
    posvec[3] = 1;
    direccional = false;
}

void ColeccionFL::activar(){
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glEnable(GL_RESCALE_NORMAL);
    glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

    for (int i=0; i < fuentes.size(); i++){
        fuentes[i] -> activar(i);
    }

    // Desactivamos las fuentes sobrantes
    for (int i=fuentes.size(); i<8; i++){
        glDisable(GL_LIGHT0+i);
    }
}


MaterialLata::MaterialLata(){
    text = new Textura("../imgs/lata-coke.jpg");
}
MaterialTapasLata::MaterialTapasLata(){

}
MaterialPeonMadera::MaterialPeonMadera(){
    text = new Textura("../imgs/text-madera.jpg");
    // Duda: diferencia entre poner 1 y 2 aquí
    text->mgct = 1;
    // s proporcional a la X, t a la Y
    text->cs[0] = 2;
    text->cs[1] = 0;
    text->cs[2] = 0;
    text->cs[3] = 0;
    text->cs[0] = 0;
    text->ct[1] = 2;
    text->ct[2] = 0;
    text->ct[3] = 0;
}
MaterialPeonBlanco::MaterialPeonBlanco(){}
MaterialPeonNegro::MaterialPeonNegro(){}
