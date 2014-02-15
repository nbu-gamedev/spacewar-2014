#ifndef ACTOR_H_INCLUDED
#define ACTOR_H_INCLUDED
#include "SDL.h"
#include"SDL_image.h"
#include <stdio.h>
#define PI 3.14159265

class Actor
{
public:
    float m_x,m_y;
    float m_width,m_height;
    float m_Vx,m_Vy;
    float m_angle;
    float m_radian;
    const Uint8* m_keys;

    SDL_Texture* m_Sprite;
    SDL_Renderer* m_Render;
    SDL_Scancode m_up,m_down,m_left,m_right,m_shoot;

    Actor();
    ~Actor();

    void Init(float x,float y,float angle,char* source,SDL_Renderer* render);

    void Draw(int w_Width,int w_Height,int s_Width,int s_Height);

    virtual void Input(SDL_Event &e);
};

class Player:public Actor
{
public:
    Player(){};

    void SetInput(char* up,char* down,char* left,char* right,char* shoot);
};

class Passive:public Actor
{
public:
    Passive(){};

    void Input(SDL_Event &e) = 0;
};

#endif // ACTOR_H_INCLUDED
