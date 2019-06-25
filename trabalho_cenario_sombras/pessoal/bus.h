#ifndef BUS_H
#define BUS_H

#include <objeto.h>

class Bus : public Objeto
{
public:
    Bus();
    Model3DS *modelo;
    void desenha();
};

#endif // BUS_H
