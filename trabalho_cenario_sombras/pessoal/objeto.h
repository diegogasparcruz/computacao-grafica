#ifndef OBJETO_H
#define OBJETO_H

#include <gui.h>

class Objeto
{
public:
    Vetor3D t = Vetor3D(0,0,0);
    Vetor3D a = Vetor3D(0,0,0);
    Vetor3D s = Vetor3D(1,1,1);

    bool selecionado = false;
    bool eixo = true;
    int rt = 0;
    int rt_sol = 0;
    int tipo;
    bool drawShadow = false;
public:
    Objeto(int tipo);
    virtual void desenha();
    void quadrado();
    void cubo();
    void esfera();
    void marcador();
    void piramide();
    void triangulo();
};

#endif // OBJETO_H
