#include "home.h"

Home::Home() : Objeto(8)
{

}

void Home::desenha(){

    Objeto::desenha();

    if(selecionado){

        glPushMatrix();
            glTranslatef(0,1,0);
            glRotatef(rt+=5,0,1,0);
            glScalef(0.1,0.1,0.1);

            glPushMatrix();
                glTranslatef(-1,0,0);
                Objeto::marcador();
            glPopMatrix();

        glPopMatrix();

    }

    GUI::setColor(0,1,1);
    glPushMatrix();

        glTranslatef(0,0.5,0.38);
        glScalef(0.65,0.5,0.65);

        Objeto::piramide();
    glPopMatrix();

    glTranslatef(-0.25,0,-0.02);

    GUI::setColor(1,1,1);
    glPushMatrix();

        glTranslatef(0,0,0.3);
        glScalef(0.5,0.5,0.5);

        Objeto::cubo();
    glPopMatrix();

}
