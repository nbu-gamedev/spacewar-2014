#ifndef PASSIVE_H_INCLUDED
#define PASSIVE_H_INCLUDED
#include "Actor.h"
#include "SDL.h"
#include <vector>
#include "Animation.h"
#include "Define.h"
#include "string"
class Passive:public Actor
{
public:
    Animation *m_animation;
    vector<Animation*>hp_bar;

    int m_passive_img_width;
    int m_passive_img_height;
    int m_start_x;
    int m_start_y;
    int m_prev_x;
    int m_prev_y;
    int m_speed_x;
    int m_speed_y;
    bool m_live;
    int prev;

    Passive();
    ~Passive();
    void Init_HpBar(SDL_Renderer* render, string source,string source2);
    void Draw_HpBar(int x, int y,int percentage, SDL_Renderer* render);
    void Draw_HpBar2(int x, int y,int percentage, SDL_Renderer* render);
    void Init(float x,float y,SDL_Renderer* render, string source);
    void Draw(int x, int y,int angle, bool more, SDL_Renderer* render);
    void DrawButton (int index, SDL_Renderer* render);
    void DrawMeteorite(bool more, SDL_Renderer* render);
    void Update();
    void Random();
    //void Input(SDL_Event &e) = 0;
};

#endif // PASSIVE_H_INCLUDED
