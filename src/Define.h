#ifndef DEFINE_H_INCLUDED
#define DEFINE_H_INCLUDED

#include <stdio.h>
#include "SDL.h"
#include "SDL_image.h"

/*
Class for loading pictures.
*/
// Window options.
const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;
#define TITLE "Space War"
const int FPS = 60;


// Pointers for window and render.
SDL_Window* window;
SDL_Renderer* render;

bool Init()
{
    bool run = true;
     if(SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            printf("Fail initialize : %s\n",SDL_GetError());
            run = false;
        }
        else
        {
            printf("Initialization Success!\n");

            if(!SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1"))
            {
                printf("Warning: VSync not enabled!\n");
                run = false;
            }

            if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
            {
                printf("Warning: Linear texture filtering not enabled!\n");
                run = false;
            }

            window = SDL_CreateWindow(TITLE,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WINDOW_WIDTH,WINDOW_HEIGHT,SDL_WINDOW_SHOWN);
            if(window == NULL)
            {
                printf("ERROR creting Window : %s\n",SDL_GetError());
                run = false;
            }
            else
            {
                printf("Created Window .\n");
                render = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
                if(render == NULL)
                {
                    printf("Failed creating Render : %s\n",SDL_GetError());
                    run = false;
                }
                else
                {
                    printf("Creted Render.\n");
                    SDL_SetRenderDrawColor( render, 0xFF, 0xFF, 0xFF, 0xFF );
                    int picFlag = IMG_INIT_PNG;
                    if(!(IMG_Init(picFlag))& picFlag)
                    {
                        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                        run = false;
                    }
                }
            }
        }
        return run;
}

// Deleting the pointers.
void Close()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(render);
    IMG_Quit();
    SDL_Quit();
    printf("Successfully Destroyed window and renderer.\n");
}



#endif // DEFINE_H_INCLUDED
