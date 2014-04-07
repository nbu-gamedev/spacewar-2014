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

    int m_Acceleration;

    Vector m_V;
    int m_width,m_height;
    float m_angle;
    int m_r;

    const Uint8* m_keys;

    SDL_Texture* m_Sprite;
    SDL_Scancode m_up,m_down,m_left,m_right,m_shoot;

    Actor();
    ~Actor();

    //virtual void Update() = 0;
   // virtual void Input(SDL_Event &e) = 0;
};




#endif // ACTOR_H_INCLUDED
