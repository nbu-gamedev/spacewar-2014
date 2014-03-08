#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED
#include "SDL.h"
#include "Player.h"
#include <vector>
using namespace std;

class World
{
public:
    World();
    ~World();

    void Init(SDL_Renderer* render);

    void DestroyTexture();

    void WInput(SDL_Event &e);

    void LoadFile(char* source,SDL_Renderer* render);

    void Render(SDL_Renderer* render);

    void WUpdate();

    SDL_Texture* m_Texture;
    int m_WWidth;
    int m_WHeight;
    vector<Player*>m_Players;
};

#endif // WORLD_H_INCLUDED
