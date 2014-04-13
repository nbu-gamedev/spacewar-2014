#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED
#include "SDL.h"
#include "Player.h"
#include <vector>
#include"Actor.h"
#include "Animation.h"
#include "Passive.h"
#include "Define.h"
#include "string"

using namespace std;

class World
{
public:
    World();
    ~World();

    void Init();

    bool InitScreen();

    void DestroyTexture();

    void WInput(bool key);

    void LoadFile(string source);

    void Render();

    void WUpdate();

    SDL_Texture* m_Texture;
    SDL_Renderer* m_render;
    SDL_Window* m_window;

    // Test for Collision
    bool CheckCollision(Actor *A,Actor *B);
    double Distance(Actor *A,Actor *B);
    void Collision();
    //
    void ReadFile(string source);
    vector<string>m_projectile_src;
    int m_WWidth;
    int m_WHeight;
    vector<Player*>m_Players;
    Animation *Planet;
    Animation *Background;
    vector<Passive*> hp_bar;
};

#endif // WORLD_H_INCLUDED
