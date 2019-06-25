#include "parede.h"

Parede::Parede() : Objeto(9)
{

}

void Parede::desenha(){

    Objeto::desenha();

    if(selecionado){

        glPushMatrix();
            glTranslatef(0,2.5,0);
            glRotatef(rt+=5,0,1,0);
            glScalef(0.1,0.1,0.1);

            glPushMatrix();
                glTranslatef(-1,0,0);
                Objeto::marcador();
            glPopMatrix();

        glPopMatrix();

    }

    GUI::setColor(1,1,1);
    glPushMatrix();

        glTranslatef(-2.5,0,-2);
        glRotatef(45,1,0,0);
        glScalef(5,0.1,2.5);

        Objeto::cubo();
    glPopMatrix();

    GUI::setColor(1,1,1);
    glPushMatrix();

        glTranslatef(-2.5,0,2);
        glRotatef(90,0,1,0);
        glRotatef(90,1,0,0);
        glScalef(4.7,0.1,2.5);

        Objeto::cubo();
    glPopMatrix();

    GUI::setColor(1,1,1);
    glPushMatrix();

        glTranslatef(2.5,0,-2.7);
        glRotatef(-90,0,1,0);
        glRotatef(90,1,0,0);
        glScalef(4.7,0.1,2.5);

        Objeto::cubo();
    glPopMatrix();

}
