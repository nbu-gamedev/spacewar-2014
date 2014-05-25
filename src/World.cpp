#include "World.h"
#include <stdio.h>
#include "SDL_image.h"

World::World()
{
    m_render = NULL;
    m_window = NULL;
    Planet = NULL;
    Background_layer_one = NULL;
    Background_layer_two = NULL;
    Background_layer_three = NULL;

    m_gravity = NULL;
    m_planet_glow = NULL;
    m_score_bar = NULL;
    m_cyan_numbers = NULL;
    m_magenta_numbers = NULL;
    m_OpacityFill = NULL;
    Player1Win = NULL;
    Player2Win = NULL;
    m_main_music = NULL;
    hp_bar1 = NULL;
    hp_bar2 = NULL;

    m_WHeight = 0;
    m_WWidth = 0;
}

bool World::InitScreen()
{
     bool run = true;
     if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
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
                        else
                        {
                            m_Stick1 = SDL_JoystickOpen(0);
                            if(m_Stick1 == NULL)
                            {
                                printf("Warning: 1st Joystick FAIL\n");
                            }
                            m_Stick2 = SDL_JoystickOpen(1);
                            if(m_Stick2 == NULL)
                            {
                                printf("Warning: 2nd Joystick FAIL\n");
                            }
                                if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 4, 4048 ) < 0 )
                            {
                                printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                            }
                        }
                    }

                }
            }
        }
        m_main_music= new Sound();
        m_main_music->Init("data/music.txt");
        m_main_music->Play(true);
        SDL_JoystickEventState(SDL_ENABLE);
        return run;
}


void World::DestroyGame()
{
    for(unsigned int i = 0;i<m_Players.size();i++)
    {
        delete m_Players[i];
        m_Players[i]= NULL;
        m_Players.erase(m_Players.begin()+i);
    }
    m_Players.clear();


    for(unsigned int i = 0;i<m_meteorite.size();i++)
    {
       delete m_meteorite[i];
        m_meteorite.erase(m_meteorite.begin()+i);
    }
    m_meteorite.clear();
    for(unsigned int i = 0;i<m_meteorite_two.size();i++)
    {
       delete m_meteorite_two[i];
        m_meteorite_two.erase(m_meteorite_two.begin()+i);
    }
    m_meteorite_two.clear();
    for(unsigned int i = 0;i<m_meteorite_three.size();i++)
    {
       delete m_meteorite_three[i];
        m_meteorite_three.erase(m_meteorite_three.begin()+i);
    }
    m_meteorite_three.clear();

    delete hp_bar1;
    hp_bar1 = NULL;
    delete hp_bar2;
    hp_bar2 = NULL;
    delete Planet;
    Planet = NULL;
    delete Background_layer_one;
    Background_layer_one = NULL;
    delete Background_layer_two;
    Background_layer_two = NULL;
    delete Background_layer_three;
    Background_layer_three = NULL;
    delete m_OpacityFill;
    m_OpacityFill = NULL;

    delete m_gravity;
    m_gravity = NULL;
    delete m_planet_glow;
    m_planet_glow = NULL;
    delete m_score_bar;
    m_score_bar = NULL;
    delete m_cyan_numbers;
    m_cyan_numbers = NULL;
    delete m_magenta_numbers;
    m_magenta_numbers = NULL;
    delete Player1Win;
    Player1Win = NULL;
    delete Player2Win;
    Player2Win = NULL;
}


World::~World()
{
    for(unsigned int i = 0;i<m_Players.size();i++)
    {
        delete m_Players[i];
        m_Players[i]= NULL;
        m_Players.erase(m_Players.begin()+i);
    }
    m_Players.clear();


    for(unsigned int i = 0;i<m_meteorite.size();i++)
    {
       delete m_meteorite[i];
        m_meteorite.erase(m_meteorite.begin()+i);
    }
    m_meteorite.clear();
    for(unsigned int i = 0;i<m_meteorite_two.size();i++)
    {
       delete m_meteorite_two[i];
        m_meteorite_two.erase(m_meteorite_two.begin()+i);
    }
    m_meteorite_two.clear();
    for(unsigned int i = 0;i<m_meteorite_three.size();i++)
    {
       delete m_meteorite_three[i];
        m_meteorite_three.erase(m_meteorite_three.begin()+i);
    }
    m_meteorite_three.clear();

    delete Planet;
    delete Background_layer_one;
    delete Background_layer_two;
    delete Background_layer_three;

    delete hp_bar1;
    delete hp_bar2;
    delete m_gravity;
    delete m_planet_glow;
    delete m_score_bar;
    delete m_cyan_numbers;
    delete m_magenta_numbers;
    delete m_OpacityFill;
    delete Player1Win;
    delete Player2Win;
    delete m_explosion;
    delete m_clash;

    SDL_DestroyRenderer(m_render);
    SDL_DestroyWindow(m_window);
    SDL_JoystickClose(m_Stick1);
    SDL_JoystickClose(m_Stick2);
}

void World::Init()
{
    m_WWidth = g_WINDOW_WIDTH;
    m_WHeight = g_WINDOW_HEIGHT;


    //m_main_music->Init("data/music.txt");

    ReadFile("data/Projectile_Setup.txt");

    Player* a1 = new Player();
    a1->Init(100,100,30,"data/P1_Src.txt",m_projectile_src[1], "data/destroy_ship_1.txt",m_render);
    a1->SetInput("Up","Down","Left","Right","Right Ctrl");
    m_Players.push_back(a1);
    a1 = NULL;
    delete a1;

    Player* a2 = new Player();
    a2->Init(m_WWidth-200,m_WHeight-200,-150,"data/P2_Src.txt",m_projectile_src[2], "data/destroy_ship_2.txt",m_render);
    a2->SetInput("W","S","A","D","Left Ctrl");
    m_Players.push_back(a2);
    a2 = NULL;
    delete a2;


    Planet = new Passive();
    Planet->Init((m_WWidth/2)-(160/2), (m_WHeight/2)-(160/2),m_render,"data/background/planet.txt");

    Background_layer_one = new Animation();
    Background_layer_one->Init(m_render,"data/background/Background layer 1.txt");
    Background_layer_two = new Animation();
    Background_layer_two->Init(m_render,"data/background/Background layer 2.txt");
    Background_layer_three = new Animation();
    Background_layer_three->Init(m_render,"data/background/Background layer 3.txt");

    m_gravity = new Animation();
    m_gravity->Init(m_render,"data/background/Gravity.txt");
    m_planet_glow = new Animation();
    m_planet_glow->Init(m_render,"data/background/Planet glow.txt");
    m_explosion=new Sound();
    m_explosion->Init("data/Explosion_sound.txt");
    m_clash=new Sound();
    m_clash->Init("data/Hit_sound.txt");

    hp_bar1=new Passive();
    hp_bar1->Init_HpBar(m_render, "data/HPbarbody.txt","data/HPbarship1.txt");
    hp_bar2=new Passive();
    hp_bar2->Init_HpBar(m_render, "data/HPbarbody2.txt","data/HPbarship2.txt");

    Passive *meteorite1=new Passive();
    meteorite1->Init(0, 0, m_render, "data/background/meteorite_1.txt");
    m_meteorite.push_back(meteorite1);

    Passive *meteorite1_1=new Passive();
    meteorite1_1->Init(0, 0, m_render, "data/background/meteorite_1.txt");
    m_meteorite.push_back(meteorite1_1);

    Passive *meteorite1_2=new Passive();
    meteorite1_2->Init(0, 0, m_render, "data/background/meteorite_1.txt");
    m_meteorite.push_back(meteorite1_2);


    Passive *meteorite2=new Passive();
    meteorite2->Init(0, 0, m_render, "data/background/meteorite_2.txt");
    m_meteorite_two.push_back(meteorite2);

    Passive *meteorite2_1=new Passive();
    meteorite2_1->Init(0, 0, m_render, "data/background/meteorite_2.txt");
    m_meteorite_two.push_back(meteorite2_1);

    Passive *meteorite2_2=new Passive();
    meteorite2_2->Init(0, 0, m_render, "data/background/meteorite_2.txt");
    m_meteorite_two.push_back(meteorite2_2);


    Passive *meteorite3=new Passive();
    meteorite3->Init(0, 0, m_render, "data/background/meteorite_3.txt");
    m_meteorite_three.push_back(meteorite3);

    Passive *meteorite3_1=new Passive();
    meteorite3_1->Init(0, 0, m_render, "data/background/meteorite_3.txt");
    m_meteorite_three.push_back(meteorite3_1);

    Passive *meteorite3_2=new Passive();
    meteorite3_2->Init(0, 0, m_render, "data/background/meteorite_3.txt");
    m_meteorite_three.push_back(meteorite3_2);

    m_score_bar = new Animation();
    m_score_bar->Init(m_render,"data/background/Score_Bar.txt");

    m_cyan_numbers=new Passive();
    m_cyan_numbers->Init(642, 0, m_render, "data/background/Cyan_numbers.txt");
    m_magenta_numbers=new Passive();
    m_magenta_numbers->Init(570, 0, m_render, "data/background/Magenta_numbers.txt");

    m_OpacityFill = new Animation();
    m_OpacityFill->Init(m_render,"data/background/OpacityFill.txt");

    Player1Win = new Animation();
    Player1Win->Init(m_render,"data/background/Player1Win.txt");

    Player2Win = new Animation();
    Player2Win->Init(m_render,"data/background/Player2Win.txt");

    m_main_music->Play(true);
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
    Background_layer_one->Draw(0,0,0,true,m_render);
    for(unsigned int i = 0;i<m_meteorite.size();i++)
    {
        m_meteorite[i]->DrawMeteorite(true, m_render);
        m_meteorite[i]->Update();
    }
    Background_layer_two->Draw(0,0,0,true,m_render);
    for(unsigned int i = 0;i<m_meteorite_two.size();i++)
    {
        m_meteorite_two[i]->DrawMeteorite(true, m_render);
        m_meteorite_two[i]->Update();
    }
    if(state->m_gravity_active==1)
    {
        m_gravity->Draw((m_WWidth/2)-( m_gravity->m_img_width/2),(m_WHeight/2)-( m_gravity->m_img_height/2),1,true,m_render);
    }
    else
    {
        m_gravity->Draw((m_WWidth/2)-( m_gravity->m_img_width/2),(m_WHeight/2)-( m_gravity->m_img_height/2),0,true,m_render);
    }
    Background_layer_three->Draw(0,0,0,true,m_render);
    for(unsigned int i = 0;i<m_meteorite_three.size();i++)
    {
        m_meteorite_three[i]->DrawMeteorite(true, m_render);
        m_meteorite_three[i]->Update();
    }

    for(unsigned int i = 0;i<m_Players.size();i++)
    {
        if(m_Players[i]->m_HP>0)
        {
            m_Players[i]->Draw(m_render);
        }
        else
        {
            if(!m_Players[i]->m_once_dead) m_Players[i]->CalculateDeath();
            m_Players[i]->m_alive = m_Players[i]->Draw_Destroy_Ship(m_render);
        }
    }



    if(state->m_planet_active == 1)
    {
        m_planet_glow->Draw((m_WWidth/2)-( m_planet_glow->m_img_width/2),(m_WHeight/2)-( m_planet_glow->m_img_height/2),0,true,m_render);
        Planet->Draw((m_WWidth/2)-(Planet->m_passive_img_width/2),(m_WHeight/2)-(Planet->m_passive_img_height/2), 0, true,m_render);
    }

    int percent = (m_Players[0]->m_HP*100)/m_Players[0]->m_FullHP;
    hp_bar1->Draw_HpBar(0, 10,percent, m_render);
    int percent2 = (m_Players[1]->m_HP*100)/m_Players[1]->m_FullHP;
    hp_bar2->Draw_HpBar2(m_WWidth-(hp_bar2->m_passive_img_width), m_WHeight-(hp_bar2->m_passive_img_height),percent2, m_render);

    m_score_bar->Draw((m_WWidth/2)-(m_score_bar->m_img_width/2),0, 0, true,m_render);
    m_magenta_numbers->DrawButton (m_Players[0]->m_lives, m_render);
    m_cyan_numbers->DrawButton (m_Players[1]->m_lives, m_render);

    if(m_Players[0]->m_lives == 0||m_Players[1]->m_lives == 0)
    {

        m_OpacityFill->Draw(0,0,0,true,m_render);
        if(m_Players[0]->m_lives == 0 && !m_Players[0]->m_alive)
        {
           Player2Win->Draw((m_WWidth/2)-(Player1Win->m_img_width/2),(m_WHeight/2)-(Player1Win->m_img_height/2), 0, true,m_render);
        }
        else if(!m_Players[1]->m_alive)
        {
           Player1Win->Draw((m_WWidth/2)-(Player2Win->m_img_width/2),(m_WHeight/2)-(Player2Win->m_img_height/2), 0, true,m_render);
        }
    }
    SDL_RenderPresent(m_render);
}

void World::WInput()
{
    m_Players[0]->Input(m_Stick1);
    m_Players[1]->Input(m_Stick2);
}

int World::WUpdate()
{
       for(unsigned int i = 0;i<m_Players.size();i++)
    {
        if(m_Players[i]->m_HP <= 0 && !m_Players[i]->m_alive)
        {
            m_Players[i]->m_lives -= 1;

            if(m_Players[0]->m_lives == 0||m_Players[1]->m_lives == 0)
            {
                return 3;
            }
            else
            {
                m_Players[0]->Reset(true);
                m_Players[1]->Reset(true);
                m_Players[i]->Update();
            }
        }
        else
        {
            m_Players[i]->Update();
        }
    }
    return 1;
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
        m_Players[0]->CollisionProjectile(Planet);
        m_Players[1]->CollisionProjectile(Planet);

        if(CheckCollision(m_Players[0],Planet))
        {
            m_Players[0]->m_HP -= 100;
            m_Players[0]->ShipCollision(Planet);
            m_clash->Play(true);
        }

        if(CheckCollision(m_Players[1],Planet))
        {
            m_Players[1]->m_HP -= 100;
            m_Players[1]->ShipCollision(Planet);
            m_clash->Play(true);
        }
    }

     if(CheckCollision(m_Players[0],m_Players[1])){
        m_Players[0]->m_HP -= 20;
        m_Players[0]->ShipCollision(m_Players[1]);
        m_clash->Play(true);
     }
     if(CheckCollision(m_Players[1],m_Players[0])){
        m_Players[1]->m_HP -= 20;
        m_Players[1]->ShipCollision(m_Players[0]);
        m_clash->Play(true);
     }
 }
