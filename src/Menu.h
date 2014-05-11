#ifndef MENU_DEFINED
#define MENU_DEFINED

#include "SDL.h"
#include "Animation.h"
#include "Passive.h"
#include "Define.h"
#include <vector>
#include <string>

class GUIstate
{
public:
    GUIstate();

    bool Regionhit (Passive* button);

    int m_x;
    int m_y;
    bool m_down;

    int m_hot;
    int m_active;
    int m_planet_active;
    int m_gravity_active;
};

class Menu
{
public:
    Menu(SDL_Renderer* render, int width, int height);
    ~Menu();

    int IMGUI (GUIstate* state);

    //MENU ITEMS
    int m_WWidth;
    int m_WHeight;
    SDL_Renderer* m_render;

    Animation *Menu_layer1;
    Animation *Menu_layer2;
    Animation *Menu_layer3;
    Animation *Menu_layer4;
    Passive *Play;
    Passive *Quit;
    Passive *Planet;
    Passive *Gravity;
};

#endif //MENU_DEFINED
