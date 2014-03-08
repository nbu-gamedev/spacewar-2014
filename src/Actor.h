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

    float m_width,m_height;
    float m_angle;
    float m_r;


    const Uint8* m_keys;

    SDL_Texture* m_Sprite;
    SDL_Renderer* m_Render;
    SDL_Scancode m_up,m_down,m_left,m_right,m_shoot;

    Actor();
    ~Actor();

    void Init(float x,float y,float angle,char* source,SDL_Renderer* render);

    void Draw(int w_Width,int w_Height,int s_Width,int s_Height);

    virtual void Update() = 0;

    virtual void Input(SDL_Event &e) = 0;
};


class Passive:public Actor
{
public:
    Passive(){};
    void Input(SDL_Event &e) = 0;
};

#endif // ACTOR_H_INCLUDED
