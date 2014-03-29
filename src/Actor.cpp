#include "Actor.h"

Actor::Actor(){
    m_width = 0;
    m_height = 0;
    m_angle = 0;
    m_r = 0;

    m_Sprite = NULL;
    m_keys = NULL;
};

Actor::~Actor()
{
    SDL_DestroyTexture(m_Sprite);
    printf("Destroyed Actor Objects!!!\n");
}






