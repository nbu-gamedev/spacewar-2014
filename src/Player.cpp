#include "Player.h"

Player::Player(){
    m_width = 0;
    m_height = 0;
    m_angle = 0.0f;
    m_r = 0;
    m_shooting = 0;
    draw_angle = 0;

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
    m_Acceleration = 1;

    m_V.SetXY(0,0);
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
    bool keydown;
    if(e.type == SDL_KEYDOWN)
    {
    m_keys = SDL_GetKeyboardState(NULL);
    if(m_keys[m_up])
        {
            if(m_V.m_x < 8)
            {
                m_V = m_V + m_Acceleration;
            }
        }

        if(m_keys[m_down])
            {
                if(m_V.m_x > -8){
                    m_V = m_V- m_Acceleration;
                }
            }

        if(m_keys[m_left])
            {
                m_angle -= 9.0f;
                draw_angle -= 9.0f;
            }

        if(m_keys[m_right])
            {
                m_angle += 9.0f;
                draw_angle += 9.0f;
            }

        if(m_keys[m_shoot])
            {
                m_shooting = true;
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
    m_animate.Draw(m_cordinates.m_x, m_cordinates.m_y,draw_angle,true,render);
    if(m_shooting)
    {
        AddProjectile(render);
        m_shooting = false;
    }

    for(unsigned int i = 0;i<m_Projectiles.size();i++){
        m_Projectiles[i]->Draw(render);
    }
}

void Player::WallCollision(int width,int height){
    Vector Normal;
    Normal.SetXY(0,0);

    if(m_cordinates.m_x + m_width >= width){
        Normal.SetXY(-1,0);
        CalcolateCollision(Normal);
    }
    else
    if(m_cordinates.m_x <= 0){
        Normal.SetXY(1.0f,0.0f);
        CalcolateCollision(Normal);
    }
    else
    if(m_cordinates.m_y + m_height >= height){
        Normal.SetXY(0.0f,-1.0f);
        CalcolateCollision(Normal);
    }
    else
    if(m_cordinates.m_y <= 0){
        Normal.SetXY(0.0f,1.0f);
        CalcolateCollision(Normal);
    }
}

void Player::CalcolateCollision(Vector other)
{
    printf("I -Heading[x]=%f [y]=%f [Angle]=%f Vel[x]=%f [y]=%f\n",m_heading.m_x,m_heading.m_y,m_angle,m_V.m_x,m_V.m_y);

    float Dot = (m_heading.DotProduction(other))*2;
    m_heading = (m_heading-(other*Dot))/other.Length();
    m_angle = m_heading.CollisionAngle(other);
    m_heading.Rotate(m_angle);
    draw_angle = 90 + m_angle;

    printf("II -Heading[x]=%f [y]=%f [Angle]=%f Vel[x]=%f [y]=%f Dot=%f\n",m_heading.m_x,m_heading.m_y,m_angle,m_V.m_x,m_V.m_y,Dot);
}





