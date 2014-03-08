#include "Actor.h"

Actor::Actor(){};

Actor::~Actor()
{
    SDL_DestroyTexture(m_Sprite);
    SDL_DestroyRenderer(m_Render);
    printf("Destroyed Actor Objects!!!\n");
}

void Actor::Draw(int w_Width,int w_Height,int s_Width,int s_Height)
{
    SDL_Rect position;
    position.x = m_cordinates.m_x;
    position.y = m_cordinates.m_y;
    position.w = m_width;
    position.h = m_height;

    SDL_RenderCopyEx(m_Render,m_Sprite,NULL,&position,m_angle,NULL,SDL_FLIP_NONE);
}





