#include "Player.h"

void Player::Init(float x,float y,float angle,char* source,SDL_Renderer* render)
{
    m_cordinates.SetXY(x,y);
    m_V.SetXY(0,0);
    m_Acceleration.SetXY(1,1);

    m_angle = angle;
    m_Render = render;
    m_shooting = false;

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

        m_r = m_width/2;
        m_center.SetXY(m_cordinates.m_x + (m_width/2), m_cordinates.m_y + (m_height/2));

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

void Player::Input(SDL_Event &e)
{
    m_keys = SDL_GetKeyboardState(NULL);

    if(e.type == SDL_KEYDOWN)
     {
        if(m_keys[m_up])
            {
                if(m_V.m_x < 8)
                {
                    m_V += m_Acceleration;
                }
            }
        if(m_keys[m_down])
            {
                if(m_V.m_x > -8){
                    m_V -= m_Acceleration;
                }
            }
        if(m_keys[m_left])
            {
                m_angle -= 8;
            }
        if(m_keys[m_right])
            {
                m_angle += 8;
            }
        if(m_keys[m_shoot])
            {
                m_shooting = true;
                printf("Pressed shoot button. \n");
            }
     }

     if(e.type == SDL_KEYUP){

        if(m_keys[m_up])
        {
            m_V += m_Acceleration;
        }
        if(m_keys[m_down])
        {
            m_V -= m_Acceleration;
        }
        if(m_keys[m_left])
        {
            m_angle -= 8;
        }
        if(m_keys[m_right])
        {
            m_angle += 8;
        }
        if(m_keys[m_shoot])
        {
            m_shooting = false;
        }
     }
     m_heading.Rotate(m_angle);
}

void Player::Update()
{
    m_center += m_heading*m_V;
    m_cordinates += m_heading*m_V;

    if(m_shooting){
            Vector head = m_center + m_heading*m_r;
            Projectyle *NewProjectyle = new Projectyle();
            NewProjectyle->Init(m_heading,head);
            m_Projectyles.push_back(NewProjectyle);
    }

}
