#include "Ship.h"
#include <stdio.h>
Ship::Ship(int x1,int y1,char p)
{
    if(p == '1')
    {
       ValX = 5;
       ValY = 5;
    }
    else
    {
       ValX = -5;
       ValY = -5;
    }
    x = x1;
    y = y1;
    angle = 0;
    player = p;

    MaxSpeed = 15;
    speed = 1;
    angle_Var = 20;
    Colusion = false;
}

void Ship::CheckColusion(int pX,int pY,int pW,int pH)
{
    Ship_r = GetWidth()/2;
    double Ship2 = pW/2;
    double dX= pX-x;
    double dY = pY-y;
    double distance = dX*dX + dY*dY;

    if(distance < (Ship_r + Ship2) * (Ship_r + Ship2))
    {
        Colusion = true;
    }
    else
    {
        Colusion = false;
    }


}
void Ship::Update()
{
        if( x < 0)
        {
            angle = -angle-180;
            x += ValX*cos(angle*PI/180);
            y += ValY*sin(angle*PI/180);
        }
        else if(x+GetWidth() > 1024)
        {
            angle = -angle+180;
            x += ValX*cos(angle*PI/180);
            y += ValY*sin(angle*PI/180);
        }
        else if(y < 0)
        {
            angle = -angle;
            x += ValX*cos(angle*PI/180);
            y += ValY*sin(angle*PI/180);

        }
        else if(y+GetHeight() > 768)
        {
            angle = -angle;
            x += ValX*cos(angle*PI/180);
            y += ValY*sin(angle*PI/180);
        }
        else if (Colusion)
        {
            printf("Collusion between Ship and Planet !\n");
            x -= ValX*cos(angle*PI/180);
            y -= ValY*sin(angle*PI/180);
        }
        else
        {
           x += ValX*cos(angle*PI/180);
           y += ValY*sin(angle*PI/180);
        }
}

void Ship::Input(SDL_Event &e)
{
     if(e.type == SDL_KEYDOWN)
        {
            keys = SDL_GetKeyboardState(NULL);
            if(player == '1')
            {
                if(keys[SDL_SCANCODE_UP]){if((ValX < MaxSpeed) || (ValY < MaxSpeed)){ValY += speed;}}
                if(keys[SDL_SCANCODE_DOWN]){if((ValX > -MaxSpeed) || (ValY > -MaxSpeed)){ValY -= speed;}}
                if(keys[SDL_SCANCODE_LEFT]){angle -= angle_Var;}
                if(keys[SDL_SCANCODE_RIGHT]){angle += angle_Var;}
            }
            if(player == '2')
            {
                if(keys[SDL_SCANCODE_W]){if((ValX > -MaxSpeed) || (ValY > -MaxSpeed)){ValY -= speed;}}
                if(keys[SDL_SCANCODE_S]){if((ValX < MaxSpeed) || (ValY < MaxSpeed)){ValY += speed;}}
                if(keys[SDL_SCANCODE_A]){angle -= angle_Var;}
                if(keys[SDL_SCANCODE_D]){angle += angle_Var;}
            }
        }
}

void Ship::readFilles(SDL_Renderer* render)
{
    if(player == '1')
    {
        LoadFile("media/dot.png",render);
    }
    else
    {
        LoadFile("media/dot.png",render);
    }

}

void Ship::Draw(SDL_Renderer* render)
{
    if(player == '1')
    {
        Visualization(x,y,angle,SDL_FLIP_NONE,render);
    }
    else
    {
        Visualization(x,y,angle,SDL_FLIP_NONE,render);
    }

}

