#include "Menu.h"
#include <stdio.h>

//IMGUI state
GUIstate::GUIstate()
{
    m_x=0;
    m_y=0;
    m_down=false;
    m_hot=0;
    m_active=0;
    m_planet_active=-1;
    m_gravity_active=-1;
}
bool GUIstate::Regionhit(Passive* button)
{
    if(m_x < button->m_coordinates.m_x ||
       m_y < button->m_coordinates.m_y ||
       m_x > button->m_coordinates.m_x+button->g_img_width ||
       m_y > button->m_coordinates.m_y+button->g_img_height)
    {
        return false;
    }
    return true;
}

//Menu class
Menu::Menu (SDL_Renderer* render, int width, int height)
{
    m_render = render;
    m_WWidth = width;
    m_WHeight = height;

    Menu_layer1 = new Animation();
    Menu_layer1->Init(m_render, "data/menu/Menu_layer1.txt");

    Play = new Passive();
    Play->Init(797, 301, m_render, "data/menu/Play_button.txt");

    Quit = new Passive();
    Quit->Init(689, 500, m_render, "data/menu/Quit_button.txt");

    Planet = new Passive();
    Planet->Init(273, 316, m_render,"data/menu/Planet_button.txt");

    Gravity = new Passive();
    Gravity->Init(273, 405, m_render, "data/menu/Gravity_button.txt");

    m_click=new Sound();
    m_click->Init("data/Click_sound.txt");
}

Menu::~Menu()
{
    delete Menu_layer1;
    delete Play;
    delete Quit;
    delete Planet;
    delete Gravity;
    delete m_click;
}

int Menu::IMGUI(GUIstate* state)
{
    //Clear hot item
    state->m_hot = 0;
    SDL_RenderClear(m_render);

    Menu_layer1->Draw(0,0,0,true,m_render);

    Play->DrawButton(0, m_render);      //ID 1
    Quit->DrawButton(0, m_render);      //ID 2
    Planet->DrawButton(state->m_planet_active+1, m_render);    //ID 3
    Gravity->DrawButton(state->m_gravity_active+1, m_render);   //ID 4

    //Decide which button is hot and active it upon click
    if(state->Regionhit(Play))
    {
        state->m_hot = 1;
        if(state->m_active==0 && state->m_down)
        {
            state->m_active = 1;
            m_click->Play(true);
            return 2;
        }
    }
    if(state->Regionhit(Quit))
    {
        state->m_hot = 2;
        if(state->m_active==0 && state->m_down)
        {
            state->m_active = 2;
            m_click->Play(true);
            return -1;
        }
    }
    if(state->Regionhit(Planet))
    {
        state->m_hot = 3;
        if(state->m_active==0 && state->m_down)
        {
            state->m_active = 3;
            state->m_planet_active *= -1;
            m_click->Play(true);
        }
    }
    if(state->Regionhit(Gravity))
    {
        state->m_hot = 4;
        if(state->m_active==0 && state->m_down)
        {
            state->m_active = 4;
            state->m_gravity_active *= -1;
            m_click->Play(true);
        }
    }

    //Render the hot item
    switch (state->m_hot)
    {
    case 1:
        Play->DrawButton(1, m_render);
        break;
    case 2:
        Quit->DrawButton(1,m_render);
        break;
    case 3:
        if(state->m_planet_active==1)
        {
            Planet->DrawButton(3, m_render);
        }
        else
        {
            Planet->DrawButton(1, m_render);
        }
        break;
    case 4:
        if(state->m_gravity_active==1)
        {
            Gravity->DrawButton(3, m_render);
        }
        else
        {
            Gravity->DrawButton(1, m_render);
        }
        break;
    default:
        break;
    }

    //Clear active state on mouse up else if there
    //are no buttons active forbid draging of active state
    if(!state->m_down)
    {
        state->m_active=0;
    }
    else
    {
        if(state->m_active==0)
        {
            state->m_active=-1;
        }
    }

    SDL_RenderPresent(m_render);

    return 0;
}

