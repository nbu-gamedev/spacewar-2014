#ifndef SHIP_H_INCLUDED
#define SHIP_H_INCLUDED
#include "Projectyle.h"
#include "World.h"
#include "SDL.h"
#include "math.h"
#define PI 3.14159265
/*
Class for the Ships:
- contains all thinks for the Ships
 * HP.
 * X and Y cordinates.
 * Speed.
 * Damage.
 * Angle.
*/
class Ship:public World
{
public:
    double angle;
    double ValX;
    double ValY;
    double Ship_r;
    int x;
    int y;


    Ship(int x1,int y1,char p);
    void readFilles(SDL_Renderer* render); //Open .png files.
    void Draw(SDL_Renderer* render);// Put the image  of the ship on the screen.
    void Input(SDL_Event &e);// Takes the input from the user.
    void Update();// Update the movement.
    void CheckColusion(int pX,int pY,int pW,int pH);//Cheks for colusions.
private:
    char player;
    int MaxSpeed;
    double speed;
    double angle_Var;
    const Uint8* keys;
    bool Colusion;

};


#endif // SHIP_H_INCLUDED
