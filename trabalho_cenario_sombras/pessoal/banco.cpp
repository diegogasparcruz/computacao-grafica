#include "banco.h"

Banco::Banco() : Objeto(1)
{

}

void Banco::desenha(){

    Objeto::desenha();

    if(selecionado){

        glPushMatrix();
            glTranslatef(0,0.3,0);
            glRotatef(rt+=5,0,1,0);
            glScalef(0.1,0.1,0.1);

            glPushMatrix();
                glTranslatef(-1,0,0);
                Objeto::marcador();
            glPopMatrix();

        glPopMatrix();

    }

    glPushMatrix();
        glTranslatef(-0.25,0,-0.2);
        glRotatef(-90,0,1,0);

        GUI::setColor(0.92,0.51,0.23);

        glPushMatrix();

            glTranslatef(0.1,0.15,0);
            glScalef(0.2,0.05,0.5);

            Objeto::cubo();
        glPopMatrix();

        //COSTA DO BANCO
        GUI::setColor(0.92,0.51,0.23);

        glPushMatrix();

            glTranslatef(0.12,0.15,0);
            glRotatef(110,0,0,1);
            glScalef(0.2,0.05,0.5);

            Objeto::cubo();
        glPopMatrix();

        //PERNAS DO BANCO

        GUI::setColor(0.92,0.51,0.23);

        glPushMatrix();

            glTranslatef(0.12,0,-0.05);
            glScalef(0.03,0.15,0.05);

            Objeto::cubo();
        glPopMatrix();

        glPushMatrix();

            glTranslatef(0.12,0,-0.38);
            glScalef(0.03,0.15,0.05);

            Objeto::cubo();
        glPopMatrix();

        glPushMatrix();

            glTranslatef(0.22,0,-0.05);
            glScalef(0.03,0.15,0.05);

            Objeto::cubo();
        glPopMatrix();

        glPushMatrix();

            glTranslatef(0.22,0,-0.38);
            glScalef(0.03,0.15,0.05);

            Objeto::cubo();
        glPopMatrix();

    glPopMatrix();

}

