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

    vector<Animation*>hp_bar;
    int position_x;
    int position_y;

    Passive();
    ~Passive();
    void Init(SDL_Renderer* render, string source,string source2, int x, int y);
    void Draw(int percentage, SDL_Renderer* render);

    //void Input(SDL_Event &e) = 0;
};

#endif // PASSIVE_H_INCLUDED
