#include "Passive.h"
Passive::Passive():Actor()
{
    m_animation=NULL;
    m_passive_img_width=0;
    m_passive_img_height=0;
    m_start_x=0;
    m_start_y=0;
    m_prev_x=0;
    m_prev_y=0;
    m_speed_x=0;
    m_speed_y=0;
    m_live=true;
    prev=0;
    srand (time(NULL));
}
Passive::~Passive()
{
    delete m_animation;
};
void Passive::Init_HpBar(SDL_Renderer* render, string source,string source2)
{
    Animation *hp_body=new Animation;
    hp_body->Init(render,source);
    hp_bar.push_back(hp_body);
    Animation *hp=new Animation;
    hp->Init(render,source2);
    hp_bar.push_back(hp);
    m_passive_img_width=hp_body->m_img_width;
    m_passive_img_height=hp_body->m_img_height;
};
void Passive::Draw_HpBar(int x, int y,int percentage, SDL_Renderer* render)
{
    hp_bar[0]->Draw(x,y, 0, true,render);
    hp_bar[1]->HP_Bar(x,y, 0,percentage, true,render);

}
void Passive::Draw_HpBar2(int x, int y,int percentage, SDL_Renderer* render)
{
    hp_bar[0]->Draw(x,y, 0, true,render);
    hp_bar[1]->HP_Bar(x,y-((hp_bar[1]->m_img_height)*percentage/100)+(hp_bar[1]->m_img_height), 0,percentage, true,render);

}
void Passive::Init(float x,float y,SDL_Renderer* render, string source)
{

    m_animation=new Animation;
    m_animation->Init(render,source);
    m_coordinates.SetXY(x,y);
    m_passive_img_width=m_animation->m_img_width;
    m_passive_img_height=m_animation->m_img_height;
    m_center.SetXY(m_coordinates.m_x + (m_passive_img_width/2), m_coordinates.m_y + (m_passive_img_height/2));
    m_r = m_passive_img_width/2;

    m_live=true;
    Random();
};

void Passive::Draw(int x, int y,int angle, bool more, SDL_Renderer* render)
{
    m_animation->Draw(x,y, angle, more,render);
}

void Passive::DrawButton (int index, SDL_Renderer* render)
{
    m_animation->Button(m_coordinates.m_x,m_coordinates.m_y, index, render);
}

void Passive::DrawMeteorite(bool more, SDL_Renderer* render)
{
    m_animation->Draw(m_start_x, m_start_y, 0, true, render);
}

void Passive::Update()
{
    if(((m_start_x<(g_WINDOW_WIDTH+m_animation->m_img_width))&&(m_start_y<(g_WINDOW_HEIGHT+m_animation->m_img_height)))&&((m_start_x>-m_animation->m_img_width)||(m_start_y>-m_animation->m_img_height)))
    {
    m_start_x=m_start_x+m_speed_x;
    m_start_y=m_start_y+m_speed_y;
    }
    else
    {
        m_live=false;
        Random();
    }
}

void Passive::Random()
{
    if(prev==0){
        m_start_x=rand() % g_WINDOW_WIDTH;
        m_start_y=-(m_animation->m_img_height);
        prev=1;
    }
    else
        {
        m_start_y=rand() % g_WINDOW_HEIGHT;
        m_start_x=-(m_animation->m_img_width);
        prev=0;
        }
    m_start_x=rand() % g_WINDOW_WIDTH;
    if(m_prev_x==m_start_x)
        {
            m_start_x=rand() % g_WINDOW_WIDTH;
            m_prev_x=m_start_x;
        }
    else
        m_prev_x=m_start_x;
    if(m_start_x%2==0)
    {
        m_start_x=-(m_animation->m_img_width);;
        m_start_y=rand() % g_WINDOW_HEIGHT;
        if(m_prev_y==m_start_y)
        {
            m_start_y=rand() % g_WINDOW_HEIGHT;
        }
        m_prev_y=m_start_y;
    }
    else
    {
        m_start_y=-(m_animation->m_img_height);
    }
    m_speed_x=(rand() % 2)+1;
    m_speed_y=(rand() % 2)+1;
}


