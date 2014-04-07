#include "World.h"
#include "Vector.h"
#include "Projectyle.h"
#include "Animation.h"
int main(int argc, char* args[])
{
    SDL_Event ev;
    World* world = new World();
    unsigned int time1;
    unsigned int time2;
    bool game;

    world->Init();
    game = true;

    while(game)
    {
        time1 = SDL_GetTicks();

        while(SDL_PollEvent(&ev))
        {
            if((ev.type == SDL_QUIT)||ev.key.keysym.sym == SDLK_ESCAPE)
            {
                game = false;
                break;
            }
            if(ev.type == SDL_KEYDOWN)
            {
                world->WInput(ev);
            }
        }
        world->Collision();
        world->WUpdate();
        world->Render();

        time2 = SDL_GetTicks();
        if(1000/g_FPS > time2- time1)
        {
               SDL_Delay(1000/g_FPS - (time2- time1));
        }
    }

    delete world;
    return 0;
}
