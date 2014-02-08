#ifndef PLANET_H_INCLUDED
#define PLANET_H_INCLUDED
#include "World.h"

class Planet:public World
{
public:
    Planet(int x,int y);
    ~Planet(){};
public:
    int Px;
    int Py;
    int damage;

};

#endif // PLANET_H_INCLUDED
