#include "lighting.hpp"

void MaterialEstandar::activar(){
    glDisable(GL_COLOR_MATERIAL);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, color[0]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color[1]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color[2]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color[3]);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, exponente);

    glColorMaterial(GL_FRONT_AND_BACK, GL_EMISSION);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);
    glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
    glColorMaterial(GL_FRONT_AND_BACK, GL_SPECULAR);

    glEnable(GL_COLOR_MATERIAL);

    if(text == NULL)
        glDisable( GL_TEXTURE_2D );
    else
        text->activar();
}


Textura::Textura( const std::string & archivoJPG ){
    img = new jpg::Imagen(archivoJPG);
    glGenTextures(1, &id_text);
    glBindTexture( GL_TEXTURE_2D, idTex );

    gluBuild2DMipmaps(
        GL_TEXTURE_2D, GL_RGB, img->tamX(), img->tamY(),
        GL_RGB, GL_UNSIGNED_BYTE, img->leerPixels()
    );

    // Falta desactivar textura?
}

void Textura::activar(){
    const GLenum TEXTURE_MODE = {GL_OBJECT_LINEAR, GL_EYE_LINEAR};
    const GLenum TEXTURE_RELATIVE = {GL_OBJECT_PLANE, GL_EYE_PLANE};

    glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D, idTex );

    switch(mgct){
    case 1||2:
        glEnable( GL_TEXTURE_GEN_S );
        glEnable( GL_TEXTURE_GEN_T );

        glTexGeni(GL_S, TEXTURE_MODE[i-1], GL_OBJECT_LINEAR);
        glTexGeni(GL_T, TEXTURE_MODE[i-1], GL_OBJECT_LINEAR);
        glTexGenfv(GL_S, TEXTURE_RELATIVE[i-1], cs);
        glTexGenfv(GL_T, TEXTURE_RELATIVE[i-1], cs);
        break;
    // Desactivado
    default:
        glDisable( GL_TEXTURE_GEN_S );
        glDisable( GL_TEXTURE_GEN_T );
        break;
    }
}


FuenteDireccional::FuenteDireccional( float alpha_inicial, float beta_inicial ){
    long_rot = alpha_inicial;
    lat_rot = beta_inicial;
    posvec[3] = 1;
}

void FuenteDireccional::variarAngulo( int i, unsigned angulo, float incremento){
    if (angulo == 0)
        long_rot += incremento;
    if (angulo == 1)
        lat_rot += incremento;

    activar(i);
}


void FuenteLuz::activar(int i){
    glEnable (GL_LIGHT0+i);

    // Fuente de luz direccional
    if (!posvec[3]){
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
}

FuentePosicional::FuentePosicional( const Tupla3f & posicion ){
    posvec[0] = posicion(X);
    posvec[1] = posicion(Y);
    posvec[2] = posicion(Z);
    posvec[3] = 1;
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
