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

                m_render = SDL_CreateRenderer(m_window,-1,SDL_RENDERER_TARGETTEXTURE);

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
                    else
                    {
                        if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
                        {
                            printf("Warning: Scale Quality not enabled!\n");
                            run = false;
                        }
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

        ReadFile("data/Projectile_Setup.txt");

        Player* a1 = new Player();
        a1->Init(10,100,-90,"data/ship_1.txt",m_projectile_src[1],m_render);
        a1->SetInput("Up","Down","Left","Right","Right Ctrl");
        m_Players.push_back(a1);

        Player* a2 = new Player();
        a2->Init(10,200,-90,"data/ship_2.txt",m_projectile_src[2],m_render);
        a2->SetInput("W","S","A","D","Left Ctrl");
        m_Players.push_back(a2);

        Planet = new Animation();
        Planet->Init(m_render,"data/planet.txt");

        Background = new Animation();
        Background->Init(m_render,"data/background.txt");


    Passive *bar=new Passive();
    bar->Init(m_render, "data/HPbarbody.txt","data/HPbarship1.txt", 0, 10);
    hp_bar.push_back(bar);
    Passive *bar2=new Passive();
    bar2->Init(m_render, "data/HPbarbody2.txt","data/HPbarship2.txt", 1240, 10);
    hp_bar.push_back(bar2);

    }
    else{
        printf("ERROR with INIT SCREEN !\n");
    }
}

void World::ReadFile(string source)
{
    string Line;
    ifstream File;
    File.open(source.c_str());

    while(!File.eof())
    {
        getline(File,Line);
        m_projectile_src.push_back(Line);
    }
    File.close();
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
    Background->Draw(0,0,0,true,m_render);

    for(unsigned int i = 0;i<m_Players.size();i++)
    {
        m_Players[i]->Draw(m_render);
    }

    Planet->Draw( (m_WWidth/2)-(Planet->img_width/2), (m_WHeight/2)-(Planet->img_width/2), 0, true,m_render);
    for(unsigned int i=0; i<hp_bar.size(); i++){
    hp_bar[i]->Draw(90, m_render);

    }

    SDL_RenderPresent(m_render);
}

void World::WInput(bool key)
{
    for(unsigned int i = 0;i<m_Players.size();i++)
    {
        m_Players[i]->Input(key);

    }
}

void World::WUpdate()
{
     for(unsigned int i = 0;i<m_Players.size();i++)
    {
        m_Players[i]->Update();
    }
}

double World::Distance(Actor *A,Actor *B){
    return sqrt((B->m_cordinates.m_x-A->m_cordinates.m_x)*(B->m_cordinates.m_x-A->m_cordinates.m_x)+
    (B->m_cordinates.m_y-A->m_cordinates.m_y)*(B->m_cordinates.m_y-A->m_cordinates.m_y));
}

 bool World::CheckCollision(Actor *A,Actor *B){
        if(Distance(A,B)<(A->m_r + B->m_r)){
        return true;
        }

        return false;
 }

 void World::Collision(){
     for(unsigned int i = 0;i < m_Players.size();i++){
        m_Players[i]->WallCollision(m_WWidth,m_WHeight);
     }

     if(CheckCollision(m_Players[0],m_Players[1])){
        printf("COLLISION!!!\n");
     }
 }




