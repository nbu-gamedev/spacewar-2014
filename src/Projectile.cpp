#include "Projectile.h"


Projectile::Projectile():Actor(){
    m_live = 0;
    m_lifetime = 0;
    m_speed = 0;
    m_cooldown = 0;
    m_damage = 0;
    m_keyshoot = NULL;

    m_startTime = 0;
    m_currentTime = 0;
    printf(" Projectile\n");
}

void Projectile::InitFromFile(string line,string source,float &item)
{
    string tmp;
    if(line.substr(0,line.find(":")) == source.c_str())
        {
            tmp = line.substr(line.find(":")+1,line.size());
            item = atoi(tmp.c_str());
        }
}
void Projectile::ReadFile(string source){

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
            InitFromFile(Line,"Speed",m_speed);
            InitFromFile(Line,"Lifetime",m_lifetime);
            InitFromFile(Line,"Damage",m_damage);
            InitFromFile(Line,"Cooldown",m_cooldown);
    }
}
    File.close();
}

Projectile::~Projectile(){

    SDL_DestroyTexture(m_Sprite);
    printf ("DESTROY PROJECTYLE \n");
}

void Projectile::Destroy()
{
    SDL_DestroyTexture(m_Sprite);
    printf ("DETED PROJECTYLE \n");
}

void Projectile::Init(string source,SDL_Renderer* render,Vector2D heading,Vector2D cordinates){

    m_live = true;
    m_startTime = SDL_GetTicks();

    m_animate.Init(render,source);

    ReadFile("data/projectile_physics.txt");

    m_width = m_animate.g_img_width;
    m_height = m_animate.g_img_height;
    m_r = m_width/2;

    m_coordinates = cordinates;
    m_heading = heading;
    m_center.SetXY(m_coordinates.m_x + (m_width/2), m_coordinates.m_y + (m_height/2));
    m_sound_shoot.Init("data/Shoot_sound.txt");
    m_sound_shoot.Play(true);
}

void Projectile::Update(){
    m_coordinates += m_heading*m_speed;
    m_center += m_heading*m_speed;
    m_currentTime = SDL_GetTicks();
    if(m_currentTime - m_startTime >= m_lifetime)
    {
        m_live = false;
    }
}


void Projectile::Draw(SDL_Renderer* render)
{
    m_animate.Draw(m_coordinates.m_x-(m_width/2), m_coordinates.m_y-(m_height/2),m_angle,true,render);
}
