#include "Player.h"

Player::Player(){
    m_width = 0;
    m_height = 0;
    m_angle = 0;
    m_r = 0;
    m_shooting = 0;

    m_Sprite = NULL;
    m_keys = NULL;
}

Player::~Player()
{
    SDL_DestroyTexture(m_Sprite);
    printf("Destroyed Player Objects!!!\n");
}

void Player::Init(float x,float y,float angle,string source,SDL_Renderer* render)
{
    m_cordinates.SetXY(x,y);
    m_V.SetXY(0,0);
    m_Acceleration.SetXY(1,1);

    m_angle = angle;
    m_shooting = false;

    m_animate.Init(render,source);
    m_width = m_animate.img_width;
    m_height = m_animate.img_height;
    m_r = m_width/2;

    m_center.SetXY(m_cordinates.m_x + (m_width/2), m_cordinates.m_y + (m_height/2));

}

void Player::SetInput(string up,string down,string left,string right,string shoot)
{
    m_up = SDL_GetScancodeFromName(up.c_str());
    m_down = SDL_GetScancodeFromName(down.c_str());
    m_left = SDL_GetScancodeFromName(left.c_str());
    m_right = SDL_GetScancodeFromName(right.c_str());
    m_shoot = SDL_GetScancodeFromName(shoot.c_str());
}

void Player::Input(SDL_Event &e)
{
    if(e.type == SDL_KEYDOWN)
     {
        m_keys = SDL_GetKeyboardState(NULL);
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
                m_angle -= 9;
            }
        if(m_keys[m_right])
            {
                m_angle += 9;
            }
        if(m_keys[m_shoot])
            {
                m_shooting = true;
            }
     }
     else if(e.type == SDL_KEYUP){
        m_keys = SDL_GetKeyboardState(NULL);

        if(m_keys[m_shoot])
        {
            m_shooting = false;
            printf("NOT Pressed shoot button. \n");
        }
     }
     m_heading.Rotate(m_angle);
}

void Player::Update()
{
    m_center += m_heading*m_V;
    m_cordinates += m_heading*m_V;

    for(unsigned int i = 0;i<m_Projectiles.size();i++){
        if(!m_Projectiles[i]->m_live){
            delete m_Projectiles[i];
            m_Projectiles.erase(m_Projectiles.begin()+i);
        }
    }

    for(unsigned int i = 0;i<m_Projectiles.size();i++){
        m_Projectiles[i]->Update();
    }
}

void Player::AddProjectile(SDL_Renderer* render)
{
    Vector coordinates = m_center + m_heading*m_r;
    Projectile *NewProjectile = new Projectile();
    NewProjectile->Init("data/projectile1.txt",render,m_heading,coordinates);
    m_Projectiles.push_back(NewProjectile);
}

void Player::Draw(SDL_Renderer* render)
{
    m_animate.Draw(m_cordinates.m_x, m_cordinates.m_y,m_angle,true,render);
    if(m_shooting)
    {
        AddProjectile(render);
        m_shooting = false;
    }

    for(unsigned int i = 0;i<m_Projectiles.size();i++){
        m_Projectiles[i]->Draw(render);
    }
}
