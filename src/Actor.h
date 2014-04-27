#ifndef ACTOR_H_INCLUDED
#define ACTOR_H_INCLUDED

#include "SDL.h"
#include"SDL_image.h"
#include <stdio.h>
#include <stdlib.h>
#include "Vector2D.h"

class Actor
{
public:
    Vector2D m_coordinates;
    Vector2D m_center;
    Vector2D m_heading;

    float m_Acceleration;

    Vector2D m_V;
    int m_width,m_height;
    float m_angle;
    float m_r;
    int m_HP;

    const Uint8* m_keys;

    SDL_Texture* m_Sprite;
    SDL_Scancode m_up,m_down,m_left,m_right,m_shoot;

    Actor();
    ~Actor();

    inline double Distance(Actor *B)
    {
        return sqrt(((B->m_center.m_x-this->m_center.m_x)*(B->m_center.m_x-this->m_center.m_x))+
                    ((B->m_center.m_y - this->m_center.m_y)*(B->m_center.m_y - this->m_center.m_y)));
    }

    inline bool CheckCollision(Actor *B)
    {
        if(Distance(B) < (this->m_r + B->m_r))
            {
                return true;
            }
        return false;
    }

};




#endif // ACTOR_H_INCLUDED
