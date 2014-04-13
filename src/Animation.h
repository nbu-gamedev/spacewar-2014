#ifndef Animation_H_INCLUDED
#define Animation_H_INCLUDED

#include "SDL.h"
#include "SDL_image.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string>
#include <fstream>
#include <vector>
#include "iostream"
#include <ctime>
#include <cstdlib>
using namespace std;

class Animation
{
public:

    ifstream m_read_file;

    float m_width,m_height;

    string m_source;
    float m_frames_x;
    float m_frames_y;
    float m_frame_duration;
    int m_repeat_from_index;
    int m_position;
    string m_animation_type;
    string m_flip;
    int repetition_searching_var;
    unsigned int m_startTime;
    unsigned int m_currentTime;

    int img_width;
    int img_height;
    int rand_index;
    int percentage_height;
    int prev_percentage;




    int m_row_elements;
    int m_column_num;


    bool m_return;

    vector<SDL_Rect>Vector_Frames;
    int vector_index;

    SDL_Surface* File;
    SDL_Texture* m_Sprite;
    SDL_RendererFlip flip;



    Animation();
    ~Animation();

    string delSpace(string &tmp_str);

    void Init(SDL_Renderer* render, string source);

    string Read_Data(string delimiter, string prefix);
    int To_int(string tmp);
    string deCaps(string tmp);

    void LOOP(int x, int y, int angle, bool m_more, SDL_Renderer* render);
    void Background(int x, int y, int angle,  bool m_more, SDL_Renderer* render);
    void Linear(int x, int y, int angle, bool m_more, SDL_Renderer* render);
    void Repeat_middle(int x, int y, int angle, bool m_more, SDL_Renderer* render);
    void Return_end(int x, int y, int angle,  bool m_more, SDL_Renderer* render);
    void Random(int x, int y, int angle, bool m_more, SDL_Renderer* render);
    void HP_Bar_body(int x, int y, int angle, bool m_more, SDL_Renderer* render);
    void HP_Bar(int x, int y, int angle, int percentage, bool m_more, SDL_Renderer* render);
    void Draw(int x, int y, int angle, bool m_more, SDL_Renderer* render);

};



#endif // Animation_H_INCLUDED
