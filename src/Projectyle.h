#ifndef PROJECTILE_H_INCLUDED
#define PROJECTILE_H_INCLUDED
#include "Actor.h"

class Projectyle:public Actor
{
public:
    bool m_live;
    float m_lifetime;
    float m_speed;

    unsigned int m_startTime;
    unsigned int m_currentTime;

    Projectyle();
    void Init(Vector heading,Vector cordinates);
    void Input(SDL_Event &e){};
    void Update();
};


#endif // PROJECTILE_H_INCLUDED
