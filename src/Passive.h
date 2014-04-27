#ifndef PASSIVE_H_INCLUDED
#define PASSIVE_H_INCLUDED
#include "Actor.h"
#include "SDL.h"
#include <vector>
#include "Animation.h"
#include "string"
class Passive:public Actor
{
public:
    Animation *m_animation;
    vector<Animation*>hp_bar;

    int g_img_width;
    int g_img_height;

    Passive();
    ~Passive();
    void Init_HpBar(SDL_Renderer* render, string source,string source2);
    void Draw_HpBar(int x, int y,int percentage, SDL_Renderer* render);
    void Draw_HpBar2(int x, int y,int percentage, SDL_Renderer* render);
    void Init(float x,float y,SDL_Renderer* render, string source);
    void Draw(int x, int y,int angle, bool more, SDL_Renderer* render);

    //void Input(SDL_Event &e) = 0;
};

#endif // PASSIVE_H_INCLUDED
