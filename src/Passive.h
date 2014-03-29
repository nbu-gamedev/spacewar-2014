#ifndef PASSIVE_H_INCLUDED
#define PASSIVE_H_INCLUDED
#include "Actor.h"

class Passive:public Actor
{
public:
    Passive(){};
    void Input(SDL_Event &e) = 0;
};

#endif // PASSIVE_H_INCLUDED
