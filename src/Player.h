#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include "Actor.h"
#include "Animation.h"
#include "Projectile.h"
#include <list>
#include <vector>

using namespace std;


class Player:public Actor
{
public:
    bool m_alive;
    bool m_shooting;
    vector<Projectile*> m_projectiles;
    Animation m_animate;
    Animation *m_back_engine;
    Animation *beam;
    Animation *m_front_engine;
    Animation *m_damage_ship;
    Animation *m_ship_destroy;
    Sound *m_sound_back_engine;
    Sound *m_sound_front_engine;
    int draw_angle;
    int  m_lives;

    string m_projectile_src;

    unsigned int m_startShoot;
    unsigned int m_currentTime;


    bool m_reduction,m_acceleration, m_once_dead;
    float m_beginX,m_beginY,m_beginAngle;
    float m_deadX,m_deadY,m_deadAngle;
    int m_FullHP;
    Sound *m_clash;

    Player();
    ~Player();
    void Init(float x,float y,float angle,string source,string projectile, string f_destroy_ship,SDL_Renderer* render);
    void SetInput(string up,string down,string left,string right,string shoot);
    void Input(SDL_Joystick* stick);
    void Update();
    void AddProjectile(SDL_Renderer* render);
    void Draw(SDL_Renderer* render);
    bool Draw_Destroy_Ship(SDL_Renderer* render);
    void ReadFile(string line,string source,string &item);
    void Reset(bool ready);

    void WallCollision(int width,int height);
    void ShipCollision(Actor *B);
    void PlayerCollision(Actor *A);
    void PlanetCollision();
    void CalcolateCollision(Vector2D other);
    void CollisionProjectile(Actor *Player);
    void CalculateDeath();

};

#endif // PLAYER_H_INCLUDED
