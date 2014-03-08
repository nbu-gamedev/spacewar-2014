#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include "Actor.h"
#include "Projectyle.h"
#include <list>
using namespace std;


class Player:public Actor
{
public:
    bool m_shooting;
    list<Projectyle*> m_Projectyles;
    list<Projectyle*>::iterator m_it;

    Player(){};

    void Init(float x,float y,float angle,char* source,SDL_Renderer* render);
    void SetInput(char* up,char* down,char* left,char* right,char* shoot);
    void Input(SDL_Event &e);
    void Update();
};

#endif // PLAYER_H_INCLUDED
