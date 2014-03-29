#include "World.h" // defines class World
#include <stdio.h>
#include "SDL_image.h"

World::World()//class World constructor
{
    m_Texture = NULL;
    m_render = NULL;
    m_window = NULL;
    Planet = NULL;

    m_WHeight = 0;
    m_WWidth = 0;
}

bool World::InitScreen()
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

            m_window = SDL_CreateWindow(TITLE,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,g_WINDOW_WIDTH,g_WINDOW_HEIGHT,SDL_WINDOW_SHOWN);
            if(m_window == NULL)
            {
                printf("ERROR creting Window : %s\n",SDL_GetError());
                run = false;
            }
            else
            {
                printf("Created Window .\n");
                m_render = SDL_CreateRenderer(m_window,-1,SDL_RENDERER_ACCELERATED);
                if(m_render == NULL)
                {
                    printf("Failed creating Render : %s\n",SDL_GetError());
                    run = false;
                }
                else
                {
                    printf("Creted Render.\n");
                    //SDL_SetRenderDrawColor( m_render, 0xFF, 0xFF, 0xFF, 0xFF );

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

World::~World()
{
    DestroyTexture();//destroy the texture
    SDL_DestroyRenderer(m_render);
    SDL_DestroyWindow(m_window);

    for(unsigned int i = 0;i<m_Players.size();i++)
    {
        delete m_Players[i];
        m_Players.erase(m_Players.begin()+i);
    }
};

void World::Init()
{
    if(InitScreen())
    {
        m_WWidth = g_WINDOW_WIDTH;
        m_WHeight = g_WINDOW_HEIGHT;

        Player* a1 = new Player();
        a1->Init(0,100,0,"data/ship1.txt",m_render);
        a1->SetInput("Up","Down","Left","Right","Right Ctrl");
        m_Players.push_back(a1);

        Player* a2 = new Player();
        a2->Init(0,200,0,"data/ship2.txt",m_render);
        a2->SetInput("W","S","A","D","Left Ctrl");
        m_Players.push_back(a2);

        Planet = new Animation();
        Planet->Init(m_render,"data/planet.txt");
    }
    else{
        printf("ERROR with INIT SCREEN !\n");
    }


}

void World::DestroyTexture()
{
    if(m_Texture!=NULL)//check if the texture is empty
    {
        SDL_DestroyTexture(m_Texture);// clear the old texture
    }
};

void World::LoadFile(string source)
{
    DestroyTexture();
    SDL_Surface* File = IMG_Load(source.c_str());//open the file of the image

    if(File == NULL)//check if file is open correctly
    {
        printf("ERROR opening image : %s , SDL_Eror: %s\n",source.c_str(),SDL_GetError());
    }
    else
    {
        m_Texture = SDL_CreateTextureFromSurface(m_render,File);//
        if(m_Texture == NULL)//check if the temporary texture is empty
        {
            printf("ERROR Creating Texture from : %s , SDL_Eror: %s\n",source.c_str(),SDL_GetError());
        }
        SDL_FreeSurface(File);//Clear the pointer to the File
    }
}

void World::Render()
{
    SDL_RenderClear(m_render);

    for(unsigned int i = 0;i<m_Players.size();i++)
    {
        m_Players[i]->Draw(m_render);
    }

    Planet->Draw( (1024/2)-(Planet->img_width/2), (768/2)-(Planet->img_width/2), 0, true,m_render);

    SDL_RenderPresent(m_render);
}

void World::WInput(SDL_Event &e)
{
    for(unsigned int i = 0;i<m_Players.size();i++)
    {
        m_Players[i]->Input(e);
    }
}

void World::WUpdate()
{
     for(unsigned int i = 0;i<m_Players.size();i++)
    {
        m_Players[i]->Update();
    }
}

