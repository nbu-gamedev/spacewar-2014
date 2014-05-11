#include "World.h"
#include <stdio.h>
#include "SDL_image.h"

World::World()
{
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

            m_window = SDL_CreateWindow(TITLE,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,g_WINDOW_WIDTH,g_WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

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
                    SDL_SetRenderDrawColor( m_render, 0xFF, 0xFF, 0xFF, 0xFF );

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
    SDL_DestroyRenderer(m_render);
    SDL_DestroyWindow(m_window);

    delete m_Players[0];
    delete m_Players[1];

    delete Planet;
    delete Background;
};

void World::Init()
{
    m_WWidth = g_WINDOW_WIDTH;
    m_WHeight = g_WINDOW_HEIGHT;

    ReadFile("data/Projectile_Setup.txt");

    Player* a1 = new Player();
    a1->Init(30,50,-90,"data/P1_Src.txt",m_projectile_src[1],m_render);
    a1->SetInput("Up","Down","Left","Right","Right Ctrl");
    m_Players.push_back(a1);

    Player* a2 = new Player();
    a2->Init(m_WWidth-200,m_WHeight-200,-90,"data/P2_Src.txt",m_projectile_src[2],m_render);
    a2->SetInput("W","S","A","D","Left Ctrl");
    m_Players.push_back(a2);


    Planet = new Passive();
    Planet->Init((m_WWidth/2)-(160/2), (m_WHeight/2)-(160/2),m_render,"data/planet.txt");

    Background = new Animation();
    Background->Init(m_render,"data/background.txt");

    Passive *bar=new Passive();
    bar->Init_HpBar(m_render, "data/HPbarbody.txt","data/HPbarship1.txt");
    hp_bar.push_back(bar);
    Passive *bar2=new Passive();
    bar2->Init_HpBar(m_render, "data/HPbarbody2.txt","data/HPbarship2.txt");
    hp_bar.push_back(bar2);
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

void World::Render(GUIstate* state)
{
    SDL_RenderClear(m_render);

    Background->Draw(0,0,0,true,m_render);

    for(unsigned int i = 0;i<m_Players.size();i++)
        {
            m_Players[i]->Draw(m_render);
        }

    if(state->m_planet_active == 1)
    {
        Planet->Draw((m_WWidth/2)-(Planet->g_img_width/2),(m_WHeight/2)-(Planet->g_img_height/2), 0, true,m_render);
    }

    int percent = (m_Players[0]->m_HP*100)/1200;
    hp_bar[0]->Draw_HpBar(0, 10,percent, m_render);
    int percent2 = (m_Players[1]->m_HP*100)/1200;
    hp_bar[1]->Draw_HpBar2(m_WWidth-(hp_bar[1]->g_img_width), m_WHeight-(hp_bar[1]->g_img_height),percent2, m_render);
    SDL_RenderPresent(m_render);
}

void World::WInput()
{
    for(unsigned int i = 0;i<m_Players.size();i++)
    {
        m_Players[i]->Input();
    }
}

void World::WUpdate()
{
     for(unsigned int i = 0;i<m_Players.size();i++)
    {
        m_Players[i]->Update();
    }
}

double World::Distance(Actor *A,Actor *B)
{
    return sqrt((B->m_center.m_x-A->m_center.m_x)*(B->m_center.m_x-A->m_center.m_x)+
    (B->m_center.m_y-A->m_center.m_y)*(B->m_center.m_y-A->m_center.m_y));
}

 bool World::CheckCollision(Actor *A,Actor *B){
        if(Distance(A,B)<A->m_r + B->m_r){
        return true;
        }

        return false;
 }

 void World::Collision(GUIstate* state)
 {
     for(unsigned int i = 0;i < m_Players.size();i++){
        m_Players[i]->WallCollision(m_WWidth,m_WHeight);
     }

     m_Players[0]->CollisionProjectile(m_Players[1]);
     m_Players[1]->CollisionProjectile(m_Players[0]);


    if(state->m_planet_active == 1)
    {
        if(CheckCollision(m_Players[0],Planet))
        {
            m_Players[0]->m_HP -= 100;
            m_Players[0]->ShipCollision(Planet);
        }

        if(CheckCollision(m_Players[1],Planet))
        {
            m_Players[1]->m_HP -= 100;
            m_Players[1]->ShipCollision(Planet);
        }
    }

     if(CheckCollision(m_Players[0],m_Players[1])){
        m_Players[0]->m_HP -= 20;
        m_Players[0]->ShipCollision(m_Players[1]);
     }
     if(CheckCollision(m_Players[1],m_Players[0])){
        m_Players[1]->m_HP -= 20;
        m_Players[1]->ShipCollision(m_Players[0]);
     }
 }




