#ifndef PROJECTILE_H_INCLUDED
#define PROJECTILE_H_INCLUDED
#include "Actor.h"
#include "Animation.h"
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

class Projectile:public Actor
{
public:
    bool m_live;
    float m_lifetime;
    float m_speed;
    float m_cooldown;
    float m_damage;
    const char* m_keyshoot;
    Animation m_animate;

    unsigned int m_startTime;
    unsigned int m_currentTime;

    Projectile();
    ~Projectile();

    void Init(string source,SDL_Renderer* render,Vector2D heading,Vector2D cordinates);
    void ReadFile(string source);
    void InitFromFile(string line,string source,float &item);

    void Input(SDL_Event &e){};
    void Update();
    void Destroy();
    void Draw(SDL_Renderer* render);
};


#endif // PROJECTILE_H_INCLUDED
