#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include "SDL.h"
#include "Player.h"
#include <vector>
#include "Actor.h"
#include "Animation.h"
#include "Sound.h"
#include "Define.h"
#include "string"
#include "Passive.h"
#include "Menu.h"

using namespace std;

class World
{
public:
    World();
    ~World();

    void Init();

    bool InitScreen();

    void WInput();

    void Render(GUIstate* state);

    int  WUpdate();

    void DestroyGame();

    SDL_Renderer* m_render;
    SDL_Window* m_window;

    bool CheckCollision(Actor *A,Actor *B);
    double Distance(Actor *A,Actor *B);
    void Collision(GUIstate* state);

    SDL_Joystick *m_Stick1;
    SDL_Joystick *m_Stick2;
    vector<Passive*> hp_bar;
    vector<Passive*> beams;
    Passive *hp_bar1;
    Passive *hp_bar2;
    void ReadFile(string source);
    vector<string>m_projectile_src;
    int m_WWidth;
    int m_WHeight;
    vector<Player*>m_Players;
    Passive *Planet;
    Passive *m_cyan_numbers;
    Passive *m_magenta_numbers;
    vector<Passive *>m_meteorite;
    vector<Passive *>m_meteorite_two;
    vector<Passive *>m_meteorite_three;
    Animation *Background_layer_one;
    Animation *Background_layer_two;
    Animation *Background_layer_three;
    Animation *m_gravity;
    Animation *m_planet_glow;
    Animation *m_score_bar;
    Sound *m_main_music;
    Sound *m_explosion;
    Sound *m_clash;
    Animation *m_OpacityFill;
    Animation *Player1Win;
    Animation *Player2Win;
};

#endif // WORLD_H_INCLUDED
