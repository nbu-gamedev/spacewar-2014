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
    string m_flip_type;
    int m_repetition_searching_var;
    unsigned int m_startTime;
    unsigned int m_currentTime;

    int g_img_width;
    int g_img_height;
    int m_rand_index;
    int m_percentage_height;
    int m_prev_percentage;




    int m_row_elements;
    int m_column_num;


    bool m_return;

    vector<SDL_Rect>m_vector_frames;
    int m_vector_index;
    int m_prev_vector_index;

    SDL_Surface* m_file;
    SDL_Texture* m_sprite;
    SDL_RendererFlip m_flip;



    Animation();
    ~Animation();

    string delSpace(string &tmp_str);
    int To_int(string tmp);
    string deCaps(string tmp);
    string Read_Data(string delimiter, string prefix);

    void Init(SDL_Renderer* render, string source);

    void Button (int x, int y, int index, SDL_Renderer* render);
    void LOOP(int x, int y, int angle, bool more, SDL_Renderer* render);
    void Background(int x, int y, int angle,  bool more, SDL_Renderer* render);
    void Linear(int x, int y, int angle, bool more, SDL_Renderer* render);
    void Repeat_middle(int x, int y, int angle, bool more, SDL_Renderer* render);
    void Return_end(int x, int y, int angle,  bool more, SDL_Renderer* render);
    void Random(int x, int y, int angle, bool more, SDL_Renderer* render);
    void HP_Bar_body(int x, int y, int angle, bool more, SDL_Renderer* render);
    void HP_Bar(int x, int y, int angle, int percentage, bool more, SDL_Renderer* render);
    void Draw(int x, int y, int angle, bool more, SDL_Renderer* render);

};



#endif // Animation_H_INCLUDED
