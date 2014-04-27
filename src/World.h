#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include "SDL.h"
#include "Player.h"
#include <vector>
#include "Actor.h"
#include "Animation.h"
#include "Define.h"
#include "string"
#include "Passive.h"


using namespace std;

class World
{
public:
    World();
    ~World();

    void Init();

    bool InitScreen();

    void WInput();

    void Render();

    void WUpdate();

    SDL_Renderer* m_render;
    SDL_Window* m_window;

    // Test for Collision
    bool CheckCollision(Actor *A,Actor *B);
    double Distance(Actor *A,Actor *B);
    void Collision();
    //
    vector<Passive*> hp_bar;
    vector<Passive*> beams;
    void ReadFile(string source);
    vector<string>m_projectile_src;
    int m_WWidth;
    int m_WHeight;
    vector<Player*>m_Players;
    Passive *Planet;
    Animation *Background;
};

#endif // WORLD_H_INCLUDED
