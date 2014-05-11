#include "Menu.h"
#include "World.h"
#include "Animation.h"
int main(int argc, char* args[])
{
    SDL_Event ev;
    World* world = new World();
    world->InitScreen();
    Menu* menu   = new Menu(world->m_render, g_WINDOW_WIDTH, g_WINDOW_HEIGHT);
    world->Init();
    unsigned int time1;
    unsigned int time2;
    bool game;
    int game_state = STATE_MENU;

    GUIstate gui_state;
    game = true;

    while(game)
    {
        time1 = SDL_GetTicks();
        while(SDL_PollEvent(&ev))
        {
            if(ev.type == SDL_MOUSEMOTION)
            {
                gui_state.m_x = ev.motion.x;
                gui_state.m_y = ev.motion.y;
            }
            if(ev.type == SDL_MOUSEBUTTONDOWN)
            {
                gui_state.m_down = true;
            }
            if(ev.type == SDL_MOUSEBUTTONUP)
            {
                gui_state.m_down = false;
            }
            if(ev.key.keysym.sym == SDLK_ESCAPE)
            {
                game_state = STATE_MENU;
            }
            if(ev.type == SDL_QUIT)
            {
                game = false;
                break;
            }
        }
        switch (game_state)
        {
        case STATE_MENU:
            //Takes the GUI state every frame and returns a game state
            //IMGUI does everything - determines items, renders, etc...
            game_state = menu->IMGUI(&gui_state);
            break;
        case STATE_GAME:
            world->WInput();
            world->Collision(&gui_state);
            world->WUpdate();
            world->Render(&gui_state);
            break;
        default:
            //Quit
            game = false;
            break;
        }

        time2 = SDL_GetTicks();
        if(1000/g_FPS > time2- time1)
        {
               SDL_Delay(1000/g_FPS - (time2- time1));
        }
    }

    delete world;
    delete menu;
    return 0;
}
