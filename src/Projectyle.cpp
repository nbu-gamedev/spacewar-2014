#include "Projectyle.h"


Projectile::Projectile(){
    m_width = 0;
    m_height = 0;
    m_angle = 0;
    m_r = 0;

    m_Sprite = NULL;
    m_keys = NULL;

    m_live = 0;
    m_lifetime = 0;
    m_speed = 0;
    m_cooldown = 0;
    m_damage = 0;
    m_keyshoot = NULL;

    m_startTime = 0;
    m_currentTime = 0;
}

void Projectile::ReadFile(string source){

    string Line;
    string tmp;
    string delimiter = ":";
    ifstream File;
    File.open(source.c_str());

    while(!File.eof())
    {
        getline(File,Line);
        if(Line[0] == '/')
        {
            printf("Comment: %s\n",Line.c_str());
        }
        else
        {
            if(Line.substr(0,Line.find(delimiter)) == "Speed")
            {
                tmp = Line.substr(Line.find(delimiter)+1,Line.size());
                m_speed = atoi(tmp.c_str());
               // printf("SPEED : %f \n",m_speed);
            }
            else if(Line.substr(0,Line.find(delimiter)) == "Number_Projectyles")
            {
                tmp = Line.substr(Line.find(delimiter)+1,Line.size());
               // printf("Number Projectiles: %s \n",tmp.c_str());
            }
            else if(Line.substr(0,Line.find(delimiter)) == "Lifetime")
            {
                tmp = Line.substr(Line.find(delimiter)+1,Line.size());
                m_lifetime = atoi(tmp.c_str());
              //  printf("Lifetime: %f \n",m_lifetime);
            }
            else if(Line.substr(0,Line.find(delimiter)) == "Damage")
            {
                tmp = Line.substr(Line.find(delimiter)+1,Line.size());
                m_damage = atoi(tmp.c_str());
              //  printf("DAMAGE: %f \n",m_damage);
            }
            else if(Line.substr(0,Line.find(delimiter)) == "Key")
            {
                tmp = Line.substr(Line.find(delimiter)+1,Line.size());
                m_keyshoot = tmp.c_str();
            }
            else if(Line.substr(0,Line.find(delimiter)) == "Cooldown")
            {
                tmp = Line.substr(Line.find(delimiter)+1,Line.size());
                m_cooldown = atoi(tmp.c_str());
            }
            else if(Line.substr(0,Line.find(delimiter)) == "Version")
            {
                tmp = Line.substr(Line.find(delimiter)+1,Line.size());
             //   printf("Version : %s\n",tmp.c_str());
            }
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

void Projectile::Init(string source,SDL_Renderer* render,Vector heading,Vector cordinates){

    m_live = true;
    m_startTime = SDL_GetTicks();

    m_animate.Init(render,source);

    ReadFile("data/Projectyle1.txt");

    m_width = m_animate.m_width/m_animate.m_frames_x;
    m_height = m_animate.m_height/m_animate.m_frames_y;
    m_r = m_width/2;

    m_cordinates = cordinates;
    m_heading = heading;
    m_center.SetXY(m_cordinates.m_x + (m_width/2), m_cordinates.m_y + (m_height/2));
}

void Projectile::Update(){
    m_currentTime = SDL_GetTicks();
    if(m_currentTime - m_startTime >= m_lifetime){

        m_live = false;

    }else{
        m_cordinates += m_heading*m_speed;
    }
}

void Projectile::SetCordinates(Vector heading,Vector cordinates){

    m_cordinates = cordinates;
    m_heading = heading;

}

void Projectile::Draw(SDL_Renderer* render)
{
    m_animate.Draw(m_cordinates.m_x, m_cordinates.m_y-(m_height/2),m_angle,true,render);
}
