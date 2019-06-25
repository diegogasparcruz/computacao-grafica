#include "pessoa.h"

Pessoa::Pessoa() : Objeto(3)
{
    //srand(time(NULL));
    pele = (rand()%400)/200.0 - .5;
    //srand(time(NULL)+5);
    camisar = ((rand())%100)/100.0;
    //srand(time(NULL)+1);
    camisag = ((rand())%100)/100.0;
    //srand(time(NULL)+3);
    camisab = (rand()%100)/100.0;
}

void Pessoa::desenha(){

    Objeto::desenha();

    if(selecionado){

        glPushMatrix();
            glTranslatef(0,0.55,0);
            glRotatef(rt+=5,0,1,0);
            glScalef(0.1,0.1,0.1);

            glPushMatrix();
                glTranslatef(-1,0,0);
                Objeto::marcador();
            glPopMatrix();

        glPopMatrix();

    }

    glPushMatrix();

        glTranslatef(-0.01,0.01,-0.01);

        // CABEÇA DA PESSOA
        GUI::setColor(0.23+pele,0.19+pele,0.15+pele);

        glPushMatrix();
            glTranslatef(0,0.48,0);
            glScalef(0.01,0.01,0.01);

            Objeto::esfera();
        glPopMatrix();

        // BRAÇOS DA PESSOA

        glPushMatrix(); // DIREITO
            glTranslatef(-0.05,0.35,0);
            glRotatef(155,0,0,1);
            glScalef(0.5,0.6,0.5);
            glScalef(0.01,0.03,0.01);

            Objeto::esfera();
        glPopMatrix();

        glPushMatrix(); // ESQUERDO
            glTranslatef(0.09,0.32,0);
            glRotatef(30,0,0,1);
            glScalef(0.5,0.6,0.5);
            glScalef(0.01,0.03,0.01);

            Objeto::esfera();
        glPopMatrix();

        // TRONCO DA PESSOA;
        GUI::setColor(camisar,camisag,camisab);
        glPushMatrix();

            glTranslatef(0,0.28,0);
            glScalef(0.01,0.03,0.01);

            Objeto::esfera();
        glPopMatrix();

        // PERNAS DA PESSOA
        glPushMatrix(); // DIREITA

            glTranslatef(-0.03,0.1,0);
            //glRotatef(155,0,0,1);
            glScalef(0.5,1,0.5);
            glScalef(0.01,0.03,0.01);

            Objeto::esfera();
        glPopMatrix();

        glPushMatrix(); // ESQUERDA

            glTranslatef(0.04,0.1,0);
            //glRotatef(30,0,0,1);
            glScalef(0.5,1,0.5);
            glScalef(0.01,0.03,0.01);

            Objeto::esfera();
        glPopMatrix();

    glPopMatrix();
}
