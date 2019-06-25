#include "sol.h"

Sol::Sol() : Objeto(5)
{

}

void Sol::desenha(){

    Objeto::desenha();

    glPushMatrix();
        glRotatef(rt_sol+=2,0,1,0);

        if(selecionado){

            glPushMatrix();

                glTranslatef(2,0,-0.07);

                glPushMatrix();
                    glTranslatef(0,1,0);
                    glRotatef(rt+=5,0,1,0);
                    glScalef(0.1,0.1,0.1);

                    glPushMatrix();
                        glTranslatef(-1,0,0);
                        Objeto::marcador();
                    glPopMatrix();

                glPopMatrix();
            glPopMatrix();
        }

        GUI::setColor(1,1,0);
        glPushMatrix();

            //glTranslatef(-0.09,0.4,-0.07);
            glTranslatef(2,0.4,-0.07);
            glScalef(0.1,0.1,0.1);

            Objeto::esfera();

        glPopMatrix();

   glPopMatrix();

}
