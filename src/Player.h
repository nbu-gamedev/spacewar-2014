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
    bool m_shooting;
    vector<Projectile*> m_projectiles;
    Animation m_animate;
    Animation* m_back_engine;
    Animation *beam;
    Animation *m_front_engine;
    Animation *m_damage_ship;
    int draw_angle;

    string m_projectile_src;

    unsigned int m_startShoot;
    unsigned int m_currentTime;

    bool m_reduction,m_acceleration;


    Player();
    ~Player();
    void Init(float x,float y,float angle,string source,string projectile,SDL_Renderer* render);
    void SetInput(string up,string down,string left,string right,string shoot);
    void Input();
    void Update();
    void AddProjectile(SDL_Renderer* render);
    void Draw(SDL_Renderer* render);
    void ReadFile(string line,string source,string &item);

    void WallCollision(int width,int height);
    void ShipCollision(Actor *B);
    void PlayerCollision(Actor *A);
    void PlanetCollision();
    void CalcolateCollision(Vector2D other);
    void CollisionProjectile(Actor *Player);

};

#endif // PLAYER_H_INCLUDED
