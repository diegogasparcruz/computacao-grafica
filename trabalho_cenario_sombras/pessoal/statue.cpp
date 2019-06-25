#include "statue.h"

Statue::Statue() : Objeto(6)
{
     modelo = new Model3DS("../3ds/statue.3ds");
}

void Statue::desenha(){

    Objeto::desenha();

    if(selecionado){

        glPushMatrix();
            glTranslatef(0,0.6,0);
            glRotatef(rt+=5,0,1,0);
            glScalef(0.1,0.1,0.1);

            glPushMatrix();
                glTranslatef(-1,0,0);
                Objeto::marcador();
            glPopMatrix();

        glPopMatrix();

    }

    glPushMatrix();
        glTranslatef(0, 0.3, 0);
        glRotated(-90, 1, 0, 0);
        glScaled(0.001, 0.001, 0.001);

        modelo->draw();
    glPopMatrix();
}
