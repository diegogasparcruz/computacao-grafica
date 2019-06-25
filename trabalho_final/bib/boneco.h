#ifndef BONECO_H
#define BONECO_H
#include <gui.h>

class Boneco
{
public:
    float vira;
    double pele;
    double camisar;
    double camisag;
    double camisab;

    Boneco();
    void quadrado();
    void desenha();
    void anda(float vel);
    Model3DS *modelo;
};

#endif // BONECO_H
