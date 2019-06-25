#ifndef PISTA_H
#define PISTA_H

#include <Vetor3D.h>
#include <vector>
#include <gui.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <boneco.h>

class Pista
{
public:
    Pista();

       Boneco *boneco = new Boneco();

       float MatrizControle[4][4];
       float Mpc[4][3];

       void interpolador();
       void bezier();
       void hermite();
       void catmullrom();
       void bspline();

       void mudarMatriz();
       void andar();
       void acelerar();
       void re();
       void para();

       void desenha(std::vector<Vetor3D> pontosControle, float deltaU);

       Vetor3D pt(float u);
       Vetor3D pt1(float u);
       Vetor3D pt2(float u);

       void trecho();

       void desenhaBoneco(std::vector<Vetor3D> pontosControle, Camera *camera);

       int matrizSelecionado;

       int ic;
       double uc;
       double velocidade;
       double atrito;

};

#endif // PISTA_H
