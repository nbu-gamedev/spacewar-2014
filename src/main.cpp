#include "Define.h"
#include "Ship.h"
#include "World.h"
#include "Planet.h"

int main(int argc, char* args[])
{
    SDL_Event e;
    Ship* P1 = new Ship(0,0,'1');
    Ship* P2 = new Ship(WINDOW_WIDTH-50,WINDOW_HEIGHT - 50,'2');
    Planet planet((WINDOW_WIDTH/2)-(planet.GetWidth()/2),(WINDOW_HEIGHT/2)-(planet.GetHeight()/2));
    World* Background = new World();
    bool game;
    if(!Init())
    {
        printf("ERROR Initialization ! \n ");
    }
    else
    {
        P1->readFilles(render);
        P2->readFilles(render);
        planet.LoadFile("media/planet2.png",render);
        Background->LoadFile("media/background2.png",render);

        game = true;
        while(game)
        {
            while(SDL_PollEvent(&e))
            {
                if(e.type == SDL_QUIT)
                {
                    game = false;
                }
                if(e.key.keysym.sym == SDLK_ESCAPE)
                {
                    game = false;
                }
                P1->Input(e);
                P2->Input(e);
            }
            P1->CheckColusion(planet.GetX(),planet.GetY(),planet.GetWidth(),planet.GetHeight());
            P2->CheckColusion(planet.GetX(),planet.GetY(),planet.GetWidth(),planet.GetHeight());
            P1->Update();
            P2->Update();
            P1->CheckColusion(P2->x,P2->y,P2->GetWidth(),P2->GetHeight());
            P2->CheckColusion(P1->x,P1->y,P1->GetWidth(),P1->GetHeight());
            P1->Update();
            P2->Update();

            SDL_RenderClear(render);
            Background->Visualization(0,0,0.0,SDL_FLIP_NONE,render);
            planet.Visualization((WINDOW_WIDTH/2)-(planet.GetWidth()/2),(WINDOW_HEIGHT/2)-(planet.GetHeight()/2),0.0,SDL_FLIP_NONE,render);
            P1->Draw(render);
            P2->Draw(render);

            SDL_RenderPresent(render);
            SDL_Delay(100);
        }
        Close();
    }



    return 0;
}
