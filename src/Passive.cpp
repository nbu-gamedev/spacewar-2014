#include "Passive.h"
Passive::Passive():Actor()
{
    position_x=0;
    position_y=0;
}
Passive::~Passive()
{

};
void Passive::Init(SDL_Renderer* render, string source,string source2, int x, int y)
{
    position_x=x;
    position_y=y;
    Animation *hp_body=new Animation;
    hp_body->Init(render,source);
    hp_bar.push_back(hp_body);
    Animation *hp=new Animation;
    hp->Init(render,source2);
    hp_bar.push_back(hp);
};
void Passive::Draw(int percentage, SDL_Renderer* render)
{
    hp_bar[0]->Draw(position_x,position_y, 0, true,render);
    hp_bar[1]->HP_Bar(position_x,position_y, 0,percentage, true,render);

}
