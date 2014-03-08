#include "Define.h"
#include "World.h"
#include "Vector.h"
#include "Projectyle.h"
int main(int argc, char* args[])
{
    SDL_Event e;
    World* world = new World();
    unsigned int t1;
    //unsigned int t2;
    unsigned int t3;

    bool game;
    if(!Init())
    {
        printf("ERROR Initialization ! \n ");
    }
    else
    {
        world->Init(g_render);
        game = true;
        while(game)
        {
            t1 = SDL_GetTicks();
            while(SDL_PollEvent(&e))
            {
                if((e.type == SDL_QUIT)||e.key.keysym.sym == SDLK_ESCAPE)
                {
                    game = false;
                    break;
                }
                world->WInput(e);
            }
            world->WUpdate();

            SDL_RenderClear(g_render);
            world->Render(g_render);
            SDL_RenderPresent(g_render);

            t3 = SDL_GetTicks();
            if(1000/g_FPS > t3- t1)
            {
               SDL_Delay(1000/g_FPS - (t3- t1));
            }
        }
    }
    delete world;
    Close();
    return 0;
}
