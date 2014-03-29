#ifndef ACTOR_H_INCLUDED
#define ACTOR_H_INCLUDED

#include "SDL.h"
#include"SDL_image.h"
#include <stdio.h>
#include <stdlib.h>
#include "Vector.h"

class Actor
{
public:
    Vector m_cordinates;
    Vector m_center;
    Vector m_heading;
    Vector m_V;
    Vector m_Acceleration;

    int m_width,m_height;
    int m_angle;
    int m_r;

    const Uint8* m_keys;

    SDL_Texture* m_Sprite;
    SDL_Scancode m_up,m_down,m_left,m_right,m_shoot;

    Actor();
    ~Actor();

    virtual void Update() = 0;
    virtual void Input(SDL_Event &e) = 0;
};




#endif // ACTOR_H_INCLUDED
