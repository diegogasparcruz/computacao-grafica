#include "plaza.h"

Plaza::Plaza() : Objeto(4)
{

}

void Plaza::desenha(){

    Objeto::desenha();

    if(selecionado){

        glPushMatrix();
            glTranslatef(0,0.1,0);
            glRotatef(rt+=5,0,1,0);
            glScalef(0.1,0.1,0.1);

            glPushMatrix();
                glTranslatef(-1,0,0);
                Objeto::marcador();
            glPopMatrix();

        glPopMatrix();

    }

    glPushMatrix();

        glTranslatef(-1,0,1);

        GUI::setColor(1,1,1);
        glPushMatrix();

            glTranslatef(0,0,0.3);
            glScalef(2,0.1,2.5);

            Objeto::cubo();
        glPopMatrix();


        GUI::setColor(0,0,0);
        glPushMatrix();

            glTranslatef(-0.3,0,0.3);
            glScalef(0.3,0.1,2.5);

            Objeto::cubo();
        glPopMatrix();

        GUI::setColor(0,0,0);
        glPushMatrix();

            glTranslatef(2.3,0,0.6);
            glRotatef(90,0,1,0);
            glScalef(0.3,0.1,2.6);

            Objeto::cubo();
        glPopMatrix();

        GUI::setColor(0,0,0);
        glPushMatrix();

            glTranslatef(2,0,0.3);
            glScalef(0.3,0.1,2.5);

            Objeto::cubo();
        glPopMatrix();

        GUI::setColor(0,0,0);
        glPushMatrix();

            glTranslatef(2.3,0,-2.2);
            glRotatef(90,0,1,0);
            glScalef(0.3,0.1,2.6);

            Objeto::cubo();
        glPopMatrix();

    glPopMatrix();

}
