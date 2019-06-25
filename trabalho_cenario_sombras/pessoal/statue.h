#ifndef STATUE_H
#define STATUE_H

#include <objeto.h>

class Statue : public Objeto
{
public:
    Statue();
    Model3DS *modelo;
    void desenha();
};

#endif // STATUE_H
