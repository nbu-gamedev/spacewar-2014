#include "Player.h"

Player::Player():Actor(){

    m_shooting = 0;
    draw_angle = 0;
    m_startShoot = 0;
    m_currentTime = 0;
    m_projectile_src = "";
    m_acceleration = false;
    m_reduction = false;
    printf(" Player\n");

}

Player::~Player()
{
    SDL_DestroyTexture(m_Sprite);

    printf("Destroyed Player Objects!!!\n");
}

void Player::ReadFile(string line,string source,string &item)
 {
      string tmp;
    if(line.substr(0,line.find(":")) == source.c_str())
        {
            tmp = line.substr(line.find(":")+1,line.size());
            item = tmp;
        }
 }

void Player::Init(float x,float y,float angle,string source,string projectile,SDL_Renderer* render)
{
    m_coordinates.SetXY(x,y);
    m_Acceleration = 0.25;
    m_HP = 1200;

    m_V.SetXY(0,0);
    m_angle = angle;
    m_shooting = false;

    string back_engine,source_beam,front_engine,ship,damageship;

    string Line;
    ifstream File;
    File.open(source.c_str());
        while(!File.eof())
    {
        getline(File,Line);
        if(Line[0] == '/')
        {
            //printf("Comment: %s\n",Line.c_str());
        }
        else
        {
            ReadFile(Line,"BackEngine",back_engine);
            ReadFile(Line,"FrontEngine",front_engine);
            ReadFile(Line,"Beam",source_beam);
            ReadFile(Line,"Ship",ship);
            ReadFile(Line,"DamageShip",damageship);
        }
    }
    m_animate.Init(render,ship);
    m_back_engine = new Animation;
    m_back_engine->Init(render, back_engine);
    beam = new Animation;
    beam->Init(render, source_beam);
    m_front_engine = new Animation;
    m_front_engine->Init(render, front_engine);
    m_damage_ship=new Animation;
    m_damage_ship->Init(render, damageship);

    m_width = m_animate.g_img_width;
    m_height = m_animate.g_img_height;
    m_r = m_width/2;

    m_center.SetXY(m_coordinates.m_x + (m_width/2), m_coordinates.m_y + (m_height/2));
    m_projectile_src = projectile;
}

void Player::SetInput(string up,string down,string left,string right,string shoot)
{
    m_up = SDL_GetScancodeFromName(up.c_str());
    m_down = SDL_GetScancodeFromName(down.c_str());
    m_left = SDL_GetScancodeFromName(left.c_str());
    m_right = SDL_GetScancodeFromName(right.c_str());
    m_shoot = SDL_GetScancodeFromName(shoot.c_str());
}

void Player::Input()
{
    m_currentTime = SDL_GetTicks();
    m_keys = SDL_GetKeyboardState(NULL);
    m_acceleration = false;
    m_reduction = false;

    if(m_keys[m_up])
        {
            m_acceleration = true;
            m_reduction = false;
            if(m_V.m_x < 8.0f)
                {
                    m_V = m_V + m_Acceleration;
                }
        }

    if(m_keys[m_down])
        {
            m_acceleration = false;
            m_reduction = true;
            if(m_V.m_x > -8.0f)
                {
                    m_V = m_V- m_Acceleration;
                }
        }

    if(m_keys[m_left])
        {
            m_angle -= 3.0f;
            draw_angle -= 3.0f;
        }
    if(m_keys[m_right])
        {
            m_angle += 3.0f;
            draw_angle += 3.0f;
        }
    if(m_keys[m_shoot])
    {
        if(m_currentTime - m_startShoot >= 250 || m_startShoot==0)
        {
            m_startShoot = SDL_GetTicks();
            m_shooting = true;
        }
    }
     m_heading.Rotate(m_angle);
}

void Player::Update()
{
    m_center += m_heading*m_V;
    m_coordinates += m_heading*m_V;

    for(unsigned int i = 0;i<m_projectiles.size();i++){
        if(!m_projectiles[i]->m_live){
            delete m_projectiles[i];
            m_projectiles.erase(m_projectiles.begin()+i);
        }
    }

    for(unsigned int i = 0;i<m_projectiles.size();i++){
        m_projectiles[i]->Update();
    }
}

void Player::AddProjectile(SDL_Renderer* render)
{
    Vector2D coordinates = m_center + m_heading*m_r;
    Projectile *NewProjectile = new Projectile();
    NewProjectile->Init(m_projectile_src,render,m_heading,coordinates);
    m_projectiles.push_back(NewProjectile);
}

void Player::Draw(SDL_Renderer* render)
{
    Vector2D coordinates2 = m_center - m_heading*m_r;

    if(m_HP>600)
    {
        m_animate.Draw(m_coordinates.m_x, m_coordinates.m_y,draw_angle,true,render);
    }
    if(m_HP<=600)
    {
        m_damage_ship->Draw(m_coordinates.m_x, m_coordinates.m_y,draw_angle,true,render);
    }

    if(m_reduction)
    {
        m_front_engine->Draw(m_center.m_x-(m_front_engine->g_img_width/2),m_center.m_y-(m_front_engine->g_img_height/2),draw_angle,true,render);
    }
    if(m_acceleration)
    {
        m_back_engine->Draw(coordinates2.m_x-(m_back_engine->g_img_width/2), coordinates2.m_y-(m_back_engine->g_img_height/2), draw_angle, true,render);
    }
    beam->Draw(m_coordinates.m_x, m_coordinates.m_y,m_angle+90 ,true, render);
    if(m_shooting)
    {
        AddProjectile(render);
        m_shooting = false;
    }

    for(unsigned int i = 0;i<m_projectiles.size();i++){
        m_projectiles[i]->Draw(render);
    }
}

void Player::CollisionProjectile(Actor *Player)
{
    for(unsigned int i = 0; i < m_projectiles.size(); i++)
    {
        if(m_projectiles[i]->CheckCollision(Player))
        {
            Player->m_HP -= m_projectiles[i]->m_damage;
            m_projectiles[i]->Update();
            delete m_projectiles[i];
            m_projectiles.erase(m_projectiles.begin()+i);
        }
    }
}

void Player::WallCollision(int width,int height){
    Vector2D Normal;
    Normal.SetXY(0,0);

    if(m_coordinates.m_x + m_width >= width){
        Normal.SetXY(-1.0f,0.0f);
        CalcolateCollision(Normal);
    }

    if(m_coordinates.m_x <= 0.0f){
        Normal.SetXY(1.0f,0.0f);
        CalcolateCollision(Normal);
    }

    if(m_coordinates.m_y + m_height >= height){
        Normal.SetXY(0.0f,-1.0f);
        CalcolateCollision(Normal);
    }

    if(m_coordinates.m_y <= 0.0f){
        Normal.SetXY(0.0f,1.0f);
        CalcolateCollision(Normal);
    }
}

void Player::ShipCollision(Actor *B)
{
    Vector2D length = (m_center - B->m_center);
    Vector2D Normal = (m_center-B->m_center)/length.Length();
    CalcolateCollision(Normal);
    Update();
}

void Player::CalcolateCollision(Vector2D other)
{
    float Dot = (m_heading.DotProduction(other))*2;
    m_heading = (m_heading-(other*Dot))/other.Length();
    m_angle = m_heading.CollisionAngle(other);
    draw_angle = 90 + m_angle;
}



