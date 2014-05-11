#ifndef Sound_H_INCLUDED
#define Sound_H_INCLUDED

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
#include <SDL_mixer.h>
#include <SDL_video.h>
using namespace std;

class Sound
{
public:

    ifstream m_read_file;

    vector<Mix_Music *>m_music;
    vector<Mix_Chunk *>m_sound_effect;
    string m_sound_type;
    string m_sound_animation;
    string m_source_music1;
    string m_source_music2;
    string m_source_music3;
    string m_repeat_music;
    string m_source_chunk_first;
    string m_source_chunk_second;
    string m_source_chunk_third;
    Mix_Chunk* m_backup_sound;
    Mix_Music* m_backup_music;
    int m_prev_sound;
    int m_vector_index;
    int m_repeat_index;
    int m_vector_size;
    bool m_first_engine_sound;

    Sound();
    ~Sound();

    string delSpace(string &tmp_str);
    int To_int(string tmp);
    string deCaps(string tmp);
    string Read_Data(string delimiter, string prefix);
    void Init(string source);
    void BackgroundMusic();
    void Sound_Effect();
    void Engine_Sound(bool more);
    void Play(bool more);
};



#endif // Sound_H_INCLUDED
