#include "Passive.h"
Passive::Passive():Actor()
{
    g_img_width=0;
    g_img_height=0;
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
    g_img_width=hp_body->g_img_width;
    g_img_height=hp_body->g_img_height;
};
void Passive::Draw_HpBar(int x, int y,int percentage, SDL_Renderer* render)
{
    hp_bar[0]->Draw(x,y, 0, true,render);
    hp_bar[1]->HP_Bar(x,y, 0,percentage, true,render);

}
void Passive::Draw_HpBar2(int x, int y,int percentage, SDL_Renderer* render)
{
    hp_bar[0]->Draw(x,y, 0, true,render);
    hp_bar[1]->HP_Bar(x,y, 0,percentage, true,render);

}
void Passive::Init(float x,float y,SDL_Renderer* render, string source)
{

    m_animation=new Animation;
    m_animation->Init(render,source);
    m_coordinates.SetXY(x,y);
    g_img_width=m_animation->g_img_width;
    g_img_height=m_animation->g_img_height;
    m_center.SetXY(m_coordinates.m_x + (g_img_width/2), m_coordinates.m_y + (g_img_height/2));
    m_r = g_img_width/2;
};

void Passive::Draw(int x, int y,int angle, bool more, SDL_Renderer* render)
{
    m_animation->Draw(x,y, angle, more,render);
}
