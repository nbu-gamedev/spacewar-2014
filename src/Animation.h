#ifndef Animation_H_INCLUDED
#define Animation_H_INCLUDED
#include "SDL.h"
#include "SDL_image.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <list>
using namespace std;

class Animation
{
public:

    float m_width,m_height;

    string m_source;
    float m_frames_x;
    float m_frames_y;
    float m_framerate;
    string m_loop;
    unsigned int m_startTime;
    unsigned int m_currentTime;


    bool m_more =true;
    int m_row_elements=0;
    int m_column_num=0;

    list<SDL_Rect>List_Frames;
    list<SDL_Rect>::iterator it;

    SDL_Surface* File;



    SDL_Texture* m_Sprite;
    SDL_Renderer* m_Render;

    Animation();
    ~Animation();

    string delSpace(string &tmp_str);

    void Init(SDL_Renderer* render, string source);

    void Draw(int x, int y, int angle, bool tmp_bool_var);

};



#endif // Animation_H_INCLUDED
