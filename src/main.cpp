#include "Define.h"
#include "World.h"

int main(int argc, char* args[])
{
    SDL_Event e;
    World* world = new World();
    Uint32 start;

    bool game;
    if(!Init())
    {
        printf("ERROR Initialization ! \n ");
    }
    else
    {
        world->Init(render);
        game = true;
        while(game)
        {
            start = SDL_GetTicks();
            while(SDL_PollEvent(&e))
            {
                if((e.type == SDL_QUIT)||e.key.keysym.sym == SDLK_ESCAPE)
                {
                    game = false;
                    break;
                }
                world->WInput(e);
            }

            SDL_RenderClear(render);
            world->Render(render);
            SDL_RenderPresent(render);

            if(1000/FPS > SDL_GetTicks()- start)
            {
                SDL_Delay(1000/FPS - (SDL_GetTicks()-start));
            }
        }
    }
    delete world;
    Close();
    return 0;
}
