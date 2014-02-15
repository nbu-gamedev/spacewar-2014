#include "Actor.h"

Actor::Actor(){};

Actor::~Actor()
{
    SDL_DestroyTexture(m_Sprite);
    SDL_DestroyRenderer(m_Render);
    printf("Destroyed Actor Objects!!!\n");
}

void Actor::Init(float x,float y,float angle,char* source,SDL_Renderer* render)
{
    m_x = x;
    m_y = y;
    m_angle = angle;
    m_Render = render;
    m_Vx = 5;
    m_Vy = 5;
    m_radian = PI/180;

    SDL_Surface* File = IMG_Load(source);
    SDL_DestroyTexture(m_Sprite);
    if(File == NULL)
    {
        printf("ERROR opening image : %s , SDL_Eror: %s\n",source,SDL_GetError());
    }
    else
    {
        m_Sprite = SDL_CreateTextureFromSurface(m_Render,File);
        if(m_Sprite == NULL)
        {
            printf("ERROR Creating Texture from : %s , SDL_Eror: %s\n",source,SDL_GetError());
        }
        else
        {
            m_width = File->w;
            m_height = File->h;
        }
        SDL_FreeSurface(File);
    }
}

void Actor::Draw(int w_Width,int w_Height,int s_Width,int s_Height)
{
    SDL_Rect position;
    position.x = m_x;
    position.y = m_y;
    position.w = m_width;
    position.h = m_height;

    SDL_RenderCopyEx(m_Render,m_Sprite,NULL,&position,m_angle,NULL,SDL_FLIP_NONE);
}

void Actor::Input(SDL_Event &e)
{
    if(e.type == SDL_KEYDOWN)
     {
        m_keys = SDL_GetKeyboardState(NULL);
        if(m_keys[m_up])
            {m_y = m_y - m_Vy;}
        if(m_keys[m_down])
            {m_y = m_y + m_Vy;}
        if(m_keys[m_left])
            {m_x = m_x - m_Vx;}
        if(m_keys[m_right])
            {m_x = m_x + m_Vx;}
        if(m_keys[m_shoot])
            {printf("Pressed shoot button. \n");}
     }
}

void Player::SetInput(char* up,char* down,char* left,char* right,char* shoot)
{
    m_up = SDL_GetScancodeFromName(up);
    m_down = SDL_GetScancodeFromName(down);
    m_left = SDL_GetScancodeFromName(left);
    m_right = SDL_GetScancodeFromName(right);
    m_shoot = SDL_GetScancodeFromName(shoot);
}


