#include "boneco.h"

Boneco::Boneco()
{

    srand(time(0));
    pele = (rand()%400)/200.0 - .5;
    camisar = ((rand())%100)/100.0;
    camisag = ((rand())%100)/100.0;
    camisab = (rand()%100)/100.0;

    vira = 0;
    modelo = new Model3DS("../3ds/teste.3DS");
}

void Boneco::quadrado()
{vel

    //glPushMatrix();
        glBegin(GL_QUADS);
        glVertex3f(0,0,0);
        glNormal3f(0,0,1);
        glVertex3f(0,1,0);
        glVertex3f(1,1,0);
        glVertex3f(1,0,0);
        glEnd();
    //glPopMatrix();

}

void Boneco::desenha(){
    glPushMatrix();

        if(vira > 500) glRotated(12,0,1,0);
        else           glRotated(-12,0,1,0);
        //glScaled(.015,.015,.015);
         //gira o cara um pouco
        glScaled(2,2,2);
        glRotated(170,1,0,0);


        glPushMatrix();

            glTranslatef(-0.01,0.01,-0.01);

            // CABEÇA DA PESSOA
            GUI::setColor(0.23+pele,0.19+pele,0.15+pele);

            glPushMatrix();
                glTranslatef(0,0.48,0);
                glScalef(0.01,0.01,0.01);

                GUI::drawSphere(1,1,1,5);;
            glPopMatrix();

            // BRAÇOS DA PESSOA

            glPushMatrix(); // DIREITO
                glTranslatef(-0.05,0.35,0);
                glRotatef(155,0,0,1);
                glScalef(0.5,0.6,0.5);
                glScalef(0.01,0.03,0.01);

                GUI::drawSphere(1,1,1,5);
            glPopMatrix();

            glPushMatrix(); // ESQUERDO
                glTranslatef(0.09,0.32,0);
                glRotatef(30,0,0,1);
                glScalef(0.5,0.6,0.5);
                glScalef(0.01,0.03,0.01);

                GUI::drawSphere(1,1,1,5);
            glPopMatrix();

            // TRONCO DA PESSOA;
            GUI::setColor(camisar,camisag,camisab);
            glPushMatrix();

                glTranslatef(0,0.28,0);
                glScalef(0.01,0.03,0.01);

                GUI::drawSphere(1,1,1,5);
            glPopMatrix();

            // PERNAS DA PESSOA
            glPushMatrix(); // DIREITA

                glTranslatef(-0.03,0.1,0);
                //glRotatef(155,0,0,1);
                glScalef(0.5,1,0.5);
                glScalef(0.01,0.03,0.01);

                GUI::drawSphere(1,1,1,5);
            glPopMatrix();

            glPushMatrix(); // ESQUERDA

                glTranslatef(0.04,0.1,0);
                //glRotatef(30,0,0,1);
                glScalef(0.5,1,0.5);
                glScalef(0.01,0.03,0.01);

                GUI::drawSphere(1,1,1,5);
            glPopMatrix();

            // PRANCHA DE SURFE;
            GUI::setColor(.4,1,.1);
            glPushMatrix();

                glTranslatef(0,0,0);
                glScalef(0.026,0.006,0.08);

                GUI::drawSphere(1,1,1,5);
            glPopMatrix();

        glPopMatrix();



        //glRotated(90,1,0,0);
        //modelo->draw();
    glPopMatrix();
}

void Boneco::anda(float vel){
    vira += vel;
    if(vira > 1000.0){
        vira -= 1000.0;
    }
}


