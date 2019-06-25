#ifndef TREE_H
#define TREE_H

#include <objeto.h>

class Tree : public Objeto
{
public:
    Tree();
    Model3DS *modelo;
    void desenha();
};

#endif // TREE_H
