#include "bus.h"

Bus::Bus() : Objeto(2)
{
    modelo = new Model3DS("../3ds/Bus-Ruin_3ds.3ds");
}

void Bus::desenha()
{

    Objeto::desenha();

    if(selecionado){

        glPushMatrix();
            glTranslatef(0,0.5,0);
            glRotatef(rt+=5,0,1,0);
            glScalef(0.1,0.1,0.1);

            glPushMatrix();
                glTranslatef(-1,0,0);
                Objeto::marcador();
            glPopMatrix();

        glPopMatrix();

    }

    glPushMatrix();
        glTranslatef(0,0,0);
        glRotatef(-90,1,0,0);
        glScalef(0.02, 0.02, 0.02);

        modelo->draw();
    glPopMatrix();
}
