#include "tree.h"

Tree::Tree() : Objeto(7)
{
    modelo = new Model3DS("../3ds/Elm 3.3ds");
}

void Tree::desenha(){

    Objeto::desenha();

    if(selecionado){

        glPushMatrix();
            glTranslatef(0,1.75,0);
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
        glScalef(0.01, 0.01, 0.01);

        modelo->draw();
    glPopMatrix();

}
