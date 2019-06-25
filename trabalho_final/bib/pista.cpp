#include "pista.h"

Pista::Pista()
{
    matrizSelecionado = 3;
    mudarMatriz();
    ic = 0;
    uc = 0;
    velocidade = 0.02;
    atrito = 0.0002;
}

void Pista::acelerar(){
    if(velocidade < .5) velocidade += .001;
}

void Pista::re(){
    if(velocidade > -.5) velocidade -= .001;
}

void Pista::para(){
    velocidade = 0;
}

void Pista::andar(){

    uc += velocidade;
    if(uc > 1){
        uc = 0;
        ic++;
    }
    if(uc < 0){
        uc = .99;
        ic--;
    }

    if(velocidade > 0.00001){
        velocidade -= atrito;
    }else if(velocidade < -0.00001){
        velocidade += atrito;
    }else{
        velocidade = 0;
    }
    atrito = 0.0002 + 0.01*velocidade;
    if(atrito < 0) atrito *= -1;
}

void Pista::desenhaBoneco(std::vector<Vetor3D> pontosControle, Camera *camera){

    if(ic < 0){
        ic += pontosControle.size();
    }
    ic %= pontosControle.size();

    float p[4][3] = {
        {pontosControle[ic].x, pontosControle[ic].y, pontosControle[ic].z},
        {pontosControle[(ic+1)%pontosControle.size()].x, pontosControle[(ic+1)%pontosControle.size()].y, pontosControle[(ic+1)%pontosControle.size()].z},
        {pontosControle[(ic+2)%pontosControle.size()].x, pontosControle[(ic+2)%pontosControle.size()].y, pontosControle[(ic+2)%pontosControle.size()].z},
        {pontosControle[(ic+3)%pontosControle.size()].x, pontosControle[(ic+3)%pontosControle.size()].y, pontosControle[(ic+3)%pontosControle.size()].z}
    };

    float soma = 0;

    for(int j = 0; j < 4; j++){

        for(int k = 0; k < 3; k++){

            soma = 0;

            for(int l = 0; l < 4; l++){

                soma += MatrizControle[j][l]*p[l][k];
            }

            Mpc[j][k] = soma;
        }
    }

    Vetor3D o = pt(uc);
    Vetor3D k = pt1(uc) * (-1);
    k.normaliza();
    Vetor3D up = pt2(uc);
    Vetor3D i = up^k;
    i.normaliza();
    Vetor3D j = k^i;
    j.normaliza();

    double T[16] = {
        i.x,j.x,k.x,o.x,
        i.y,j.y,k.y,o.y,
        i.z,j.z,k.z,o.z,
        0,0,0,1
    };

   glPushMatrix();
      glMultTransposeMatrixd(T);
      //GUI::drawOrigin(1);
      boneco->desenha();

      cout << velocidade << endl;
      float ax = velocidade*3000;
      if(ax < 0) ax *= -1;
      if(ax > 1) boneco->anda(ax);
      //cout << ax << endl;
   glPopMatrix();

   Vetor3D delta = j*(-1.6) + k*(4);
   camera->c = o + delta;
   camera->u = up*-1;
   camera->e = o + k + delta + j*(-.2);
}

void Pista::mudarMatriz(){

    matrizSelecionado++;
    matrizSelecionado%=5;

    switch (matrizSelecionado) {
    case 0:
        interpolador();
        break;

    case 1:
        hermite();
        break;

    case 2:
        bezier();
        break;

    case 3:
        catmullrom();
        break;

    case 4:
        bspline();
        break;

    default:
        break;
    }

}

void Pista::interpolador(){

    float M[4][4] = {
        {-4.5, 13.5, -13.5, 4.5},
        {9, -22.5, 18, -4.5},
        {-5.5, 9, -4.5, 1},
        {1, 0, 0, 0}
    };

    for(int i = 0; i < 4; i++){

        for(int j = 0; j < 4; j++){

            MatrizControle[i][j] = M[i][j];
        }
    }

}

void Pista::bezier(){

    float M[4][4] = {
        {-1, 3, -3, 1},
        {3, -6, 3, 0},
        {-3, 3, 0, 0},
        {1, 0, 0, 0}
    };

    for(int i = 0; i < 4; i++){

        for(int j = 0; j < 4; j++){

            MatrizControle[i][j] = M[i][j];
        }
    }

}

void Pista::hermite(){

    float M[4][4] = {
        {2, -2, 1, 1},
        {-3, 3, -2, -1},
        {0, 0, 1, 0},
        {1, 0, 0, 0}
    };

    for(int i = 0; i < 4; i++){

        for(int j = 0; j < 4; j++){

            MatrizControle[i][j] = M[i][j];
        }
    }

}

void Pista::catmullrom(){

    float M[4][4] = {
        {-1/2.0, 3/2.0, -3/2.0, 1/2.0},
        {2/2.0, -5/2.0, 4/2.0, -1/2.0},
        {-1/2.0, 0, 1/2.0, 0},
        {0, 2/2.0, 0, 0}
    };

    for(int i = 0; i < 4; i++){

        for(int j = 0; j < 4; j++){

            MatrizControle[i][j] = M[i][j];
        }
    }

}

void Pista::bspline(){

    float M[4][4] = {
        {-1/6.0, 3/6.0, -3/6.0, 1/6.0},
        {3/6.0, -6/6.0, 3/6.0, 0},
        {-3/6.0, 0, 3/6.0, 0},
        {1/6.0, 4/6.0, 1/6.0, 0}
    };

    for(int i = 0; i < 4; i++){

        for(int j = 0; j < 4; j++){

            MatrizControle[i][j] = M[i][j];
        }
    }

}

void Pista::desenha(std::vector<Vetor3D> pontosControle, float deltaU){

    for(int i = 0; i < 1; i++){

        float p[4][3] = {
            {pontosControle[i].x, pontosControle[i].y, pontosControle[i].z},
            {pontosControle[(i+1)%pontosControle.size()].x, pontosControle[(i+1)%pontosControle.size()].y, pontosControle[(i+1)%pontosControle.size()].z},
            {pontosControle[(i+2)%pontosControle.size()].x, pontosControle[(i+2)%pontosControle.size()].y, pontosControle[(i+2)%pontosControle.size()].z},
            {pontosControle[(i+3)%pontosControle.size()].x, pontosControle[(i+3)%pontosControle.size()].y, pontosControle[(i+3)%pontosControle.size()].z}
        };

        float soma = 0;

        for(int j = 0; j < 4; j++){

            for(int k = 0; k < 3; k++){

                soma = 0;

                for(int l = 0; l < 4; l++){

                    soma += MatrizControle[j][l]*p[l][k];
                }

                Mpc[j][k] = soma;
            }
        }


        for(float u = 0; u <= 1; u+=deltaU){
            Vetor3D o = pt(u);
            Vetor3D k = pt1(u) * (-1);
            k.normaliza();
            Vetor3D up = pt2(u);
            Vetor3D i = up^k;
            i.normaliza();
            Vetor3D j = k^i;
            j.normaliza();

            double T[16] = {
                i.x,j.x,k.x,o.x,
                i.y,j.y,k.y,o.y,
                i.z,j.z,k.z,o.z,
                0,0,0,1
            };

           glPushMatrix();
              glMultTransposeMatrixd(T);
              glScalef(1,1,3*deltaU*pontosControle.size());
              trecho();
           glPopMatrix();

        }
    }

}

Vetor3D Pista::pt(float u){

    float U[4] = {u*u*u, u*u, u, 1};
    float aux[3];

    for(int j = 0; j < 3; j++){

        float soma = 0;

        for(int k = 0; k < 4; k++){
            soma += U[k]*Mpc[k][j];
        }

        aux[j] = soma;
    }

    Vetor3D vetor3d(aux[0],aux[1],aux[2]);

    return vetor3d;

}

Vetor3D Pista::pt1(float u){

    float U[4] = {3*(u*u), 2*u, 1, 0};
    float aux[3];

    for(int j = 0; j < 3; j++){

        float soma = 0;

        for(int k = 0; k < 4; k++){
            soma += U[k]*Mpc[k][j];
        }

        aux[j] = soma;
    }

    Vetor3D vetor3d(aux[0],aux[1],aux[2]);

    return vetor3d;

}

Vetor3D Pista::pt2(float u){

    float U[4] = {6*u, 2, 0, 0};
    float aux[3];

    for(int j = 0; j < 3; j++){

        float soma = 0;

        for(int k = 0; k < 4; k++){
            soma += U[k]*Mpc[k][j];
        }

        aux[j] = soma;
    }

    Vetor3D vetor3d(aux[0],aux[1],aux[2]);

    return vetor3d;

}

void Pista::trecho()
{

    glBegin(GL_QUADS);
        GUI::setColor(0,0,.9);
        glNormal3f(0,1,0);
        glVertex3f(-1,0,0);
        glVertex3f(-1,0,1);
        glVertex3f(1,0,1);
        glVertex3f(1,0,0);
    glEnd();

    glBegin(GL_QUADS);
        GUI::setColor(.2,.2,1);
        glNormal3f(0,1,0);
        glVertex3f(-1,0,0);
        glVertex3f(1,0,0);
        glVertex3f(1,0,1);
        glVertex3f(-1,0,1);
    glEnd();

}
