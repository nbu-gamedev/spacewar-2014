#ifndef PROJECTYLE_H_INCLUDED
#define PROJECTYLE_H_INCLUDED
#include "World.h"
class Projectyle:public World
{
public:
    int x,y;
    int Velx,Vely;
    double angle;
    Projectyle(int px,int py);
    void Move();
    void Update();
};

#endif // PROJECTYLE_H_INCLUDED
