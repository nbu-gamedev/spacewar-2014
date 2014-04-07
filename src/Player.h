#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include "Actor.h"
#include "Animation.h"
#include "Projectyle.h"
#include <list>
#include <vector>

using namespace std;


class Player:public Actor
{
public:
    bool m_shooting;
    vector<Projectile*> m_Projectiles;
    Animation m_animate;
    int draw_angle;

    Player();
    ~Player();
    void Init(float x,float y,float angle,string source,SDL_Renderer* render);
    void SetInput(string up,string down,string left,string right,string shoot);
    void Input(SDL_Event &e);
    void Update();
    void AddProjectile(SDL_Renderer* render);
    void Draw(SDL_Renderer* render);
    // Test Collision
    void WallCollision(int width,int height);
    void PlayerCollision(Actor *A);
    void PlanetCollision();
    void CalcolateCollision(Vector other);
    //


};

#endif // PLAYER_H_INCLUDED
