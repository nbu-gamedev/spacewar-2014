#include "World.h" // defines class World
#include <stdio.h>
#include "SDL_image.h"

World::World()//class World constructor
{
}

World::~World()
{
    DestroyTexture();//destroy the texture
    for(int i = 0;i<m_Players.size();i++)
    {
        delete m_Players[i];
    }
};

void World::Init(SDL_Renderer* render)
{
    m_WWidth = 1024;
    m_WHeight = 768;

    LoadFile("media/background2.png",render);

    Player* a1 = new Player();
    a1->Init(0,0,0,"media/planet2.png",render);
    a1->SetInput("Up","Down","Left","Right","Left Ctrl");
    m_Players.push_back(a1);

    Player* a2 = new Player();
    a2->Init(100,0,0,"media/planet2.png",render);
    a2->SetInput("W","S","A","D","Right Ctrl");
    m_Players.push_back(a2);
}

void World::DestroyTexture()
{
    if(m_Texture!=NULL)//check if the texture is empty
    {
        SDL_DestroyTexture(m_Texture);// clear the old texture
    }
};

void World::LoadFile(char* source,SDL_Renderer* render)
{
    DestroyTexture();
    SDL_Surface* File = IMG_Load(source);//open the file of the image

    if(File == NULL)//check if file is open correctly
    {
        printf("ERROR opening image : %s , SDL_Eror: %s\n",source,SDL_GetError());
    }
    else
    {
        m_Texture = SDL_CreateTextureFromSurface(render,File);//
        if(m_Texture == NULL)//check if the temporary texture is empty
        {
            printf("ERROR Creating Texture from : %s , SDL_Eror: %s\n",source,SDL_GetError());
        }
        SDL_FreeSurface(File);//Clear the pointer to the File
    }
}

void World::Render(SDL_Renderer* render)
{
    SDL_Rect position{0,0,1024,768};
    SDL_RenderCopyEx(render,m_Texture,NULL,&position,0,NULL,SDL_FLIP_NONE);
    for(int i = 0;i<m_Players.size();i++)
    {
        m_Players[i]->Draw(1024,768,1024,768);
    }
};

void World::WInput(SDL_Event &e)
{
    for(int i = 0;i<m_Players.size();i++)
    {
        m_Players[i]->Input(e);
    }
}



