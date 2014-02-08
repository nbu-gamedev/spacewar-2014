#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED
#include "SDL.h"
class World
{
public:
    World();
    ~World();
    void Destroy_texture();

    bool LoadFile(char* destination,SDL_Renderer* render);

    void Visualization(int x,int y,double angle,SDL_RendererFlip Flip_img,SDL_Renderer* render);

    int GetWidth();

    int GetHeight();

    int GetX();

    int GetY();

private:
    SDL_Texture* Texture;
    int Width;
    int Height;
    int Wx;
    int Wy;
};

#endif // WORLD_H_INCLUDED
