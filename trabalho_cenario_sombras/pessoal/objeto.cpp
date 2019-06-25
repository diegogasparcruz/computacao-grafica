#include "objeto.h"

Objeto::Objeto(int t)
{
    tipo = t;
}

void Objeto::desenha()
{

    glTranslatef(t.x,t.y,t.z);
    glRotatef(a.z,0,0,1);
    glRotatef(a.y,0,1,0);
    glRotatef(a.x,1,0,0);

    if(eixo){
        GUI::drawOrigin(1);
    }

    glScalef(s.x,s.y,s.z);
}

void Objeto::quadrado()
{

    //glPushMatrix();

        glBegin(GL_QUADS);
            glNormal3f(0,0,1);
            glVertex3f(0,0,0);
            glVertex3f(0,1,0);
            glVertex3f(1,1,0);
            glVertex3f(1,0,0);
        glEnd();

    //glPopMatrix();

}

void Objeto::cubo(){

    glPushMatrix();

        quadrado();

    glPopMatrix();

    glPushMatrix();

        glTranslatef(0,0,-1);
        quadrado();

    glPopMatrix();

    glPushMatrix();

        glTranslatef(0,1,0);
        glRotatef(-90,1,0,0);
        quadrado();

    glPopMatrix();

    glPushMatrix();

        glTranslatef(0,0,0);
        glRotatef(-90,1,0,0);
        quadrado();

    glPopMatrix();

    glPushMatrix();

        glRotatef(90,0,1,0);
        quadrado();

    glPopMatrix();

    glPushMatrix();

        glTranslatef(1,0,0);
        glRotatef(90,0,1,0);
        quadrado();

    glPopMatrix();

}

void Objeto::esfera(){

    GUI::drawSphere(1,1,1,5);

}

void Objeto::marcador(){

    GUI::setColor(1,0,0);

    glBegin(GL_POLYGON);
        glNormal3f(0,0,1);
        glVertex3f(0,2,0);
        glVertex3f(2,2,0);
        glVertex3f(1,0,0);
    glEnd();

    glPushMatrix();
        glTranslatef(1,0,1);
        glRotatef(90,0,1,0);

        glBegin(GL_POLYGON);
            glNormal3f(0,0,1);
            glVertex3f(0,2,0);
            glVertex3f(2,2,0);
            glVertex3f(1,0,0);
        glEnd();

    glPopMatrix();

}

void Objeto::triangulo(){

    GUI::setColor(1,0,0);

    glBegin(GL_POLYGON);
        glNormal3f(0,0,1);
        glVertex3f(0,0,0);
        glVertex3f(1,0,0);
        glVertex3f(0.5,1,0);
    glEnd();

}


void Objeto::piramide(){

    glPushMatrix();

        glTranslatef(-0.5,0,-1.05);

        glPushMatrix();
            glRotatef(30,1,0,0);

            triangulo();
        glPopMatrix();

        glPushMatrix();
            glRotatef(-30,0,0,1);
            glRotatef(-90,0,1,0);

            triangulo();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(1,0,0);
            glRotatef(30,0,0,1);
            glRotatef(-90,0,1,0);

            triangulo();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0,0,1);
            glRotatef(-30,1,0,0);

            triangulo();
        glPopMatrix();

    glPopMatrix();

    glPushMatrix();
        glTranslatef(-0.5,0,-1.05);
        glRotatef(90,1,0,0);

        quadrado();
    glPopMatrix();

}
