#include "Sound.h"

Sound::Sound()
{
    m_sound_type="";
    m_sound_animation="";
    m_source_music1="";
    m_source_music2="";
    m_source_music3="";
    m_repeat_music="";
    m_source_chunk_first="";
    m_source_chunk_second="";
    m_source_chunk_third="";
    m_prev_sound=0;
    m_vector_index=0;
    m_repeat_index=0;
    m_vector_size=0;
    m_first_engine_sound=true;
};

Sound::~Sound()
{
    for(unsigned int i =0; i<m_music.size(); i++)
    {
        m_music[i]=NULL;
    }

	for(unsigned int i =0; i<m_sound_effect.size(); i++)
    {
        Mix_FreeChunk( m_sound_effect[i] );
        m_sound_effect[i]=NULL;
    }
}

string Sound::delSpace(string &tmp_str)
{
    while(' ' == tmp_str[0] && 0<tmp_str.length()) tmp_str.erase(tmp_str.begin());
    while(' ' == tmp_str[tmp_str.length()-1] && 0<tmp_str.length()) tmp_str.erase(tmp_str.end()-1);

    return tmp_str;
}

string Sound::deCaps(string tmp)
{
    for(unsigned int i=0; i<tmp.length(); i++)
    {
        if((tmp[i]>='A')&&(tmp[i]<='Z'))
        {
            tmp[i]=(tolower(tmp[i]));
        }
    }
    return tmp;
}

string Sound::Read_Data(string delimiter, string prefix)
{
    bool more=true;
    string tmp;
    string data;

    while(((getline(m_read_file, tmp))||(true==more)))
    {

        if(m_read_file.eof())
        {
            more = false;
            m_read_file.clear();
            m_read_file.seekg(0, ios_base::beg);
            getline(m_read_file, tmp);
        }

        data=deCaps(tmp.substr(0, tmp.find(delimiter)));
        data=delSpace(data);
        prefix=deCaps(prefix);

        if(tmp[0]=='/')
        {

        }
        else
            if(data==prefix)
            {
                data=tmp.substr((tmp.find(delimiter)+1), tmp.size());
                data=delSpace(data);
                tmp="";
                return data;
            }
    }

    if((false==more) && m_read_file.eof())
    {
        data = "none";
    }

    return data;
}


void Sound::Init(string source)
{
    string delimiter = ":";
    m_read_file.open(source);
    if(m_read_file.is_open())
    {
        m_sound_type = Read_Data(delimiter, "type");
        if(m_sound_type=="music")
        {
            m_source_music1 = Read_Data(delimiter, "file1");
            m_source_music2 = Read_Data(delimiter, "file2");
            m_source_music3 = Read_Data(delimiter, "file3");
            m_repeat_music = Read_Data(delimiter, "repeat");
            cout<<m_source_music1<<endl;
            cout<<m_source_music2<<endl;
            cout<<m_source_music3<<endl;
            Mix_Music * tmp_music = Mix_LoadMUS( m_source_music1.c_str() );
            if( tmp_music == NULL )
            {
                printf( "Failed to load  music! SDL_mixer Error: %s\n", Mix_GetError() );
            }
            else
                {
                    m_music.push_back(tmp_music);
                    tmp_music=NULL;
                    cout<<"first_song"<<endl;
                }

            tmp_music = Mix_LoadMUS( m_source_music2.c_str() );
            if( tmp_music == NULL )
            {
                printf( "Failed to load  music! SDL_mixer Error: %s\n", Mix_GetError() );
            }
            else
                {
                    m_music.push_back(tmp_music);
                    tmp_music=NULL;
                    cout<<"first_song"<<endl;
                }



            tmp_music = Mix_LoadMUS( m_source_music3.c_str() );
            if( tmp_music == NULL )
            {
                printf( "Failed to load  music! SDL_mixer Error: %s\n", Mix_GetError() );
            }
            else
                {
                    m_music.push_back(tmp_music);
                    tmp_music=NULL;
                    cout<<"first_song"<<endl;
                }
            Mix_FreeMusic(tmp_music);
            if(m_repeat_music=="repeat")
            {
                m_repeat_index=-1;
            }
            else
                if(m_repeat_music=="ones")
                {
                    m_repeat_index=0;
                }
            m_vector_size=int(m_music.size());
        }
        else
            if((m_sound_type=="sound effect")||(m_sound_type=="engine sound"))
            {
                cout<<"read sound effect"<<endl;
                m_sound_animation = Read_Data(delimiter, "sound for animation");
                m_source_chunk_first = Read_Data(delimiter, "file1");
                m_source_chunk_second = Read_Data(delimiter, "file2");
                m_source_chunk_third = Read_Data(delimiter, "file3");

                Mix_Chunk * tmp_sound_effect = Mix_LoadWAV(m_source_chunk_first.c_str());
                if( tmp_sound_effect == NULL )
                {
                    printf( "Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
                }
                else
                {
                    m_sound_effect.push_back(tmp_sound_effect);
                    tmp_sound_effect=NULL;
                }

                tmp_sound_effect = Mix_LoadWAV(m_source_chunk_second.c_str());
                if( tmp_sound_effect == NULL )
                {
                    printf( "Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
                }
                else
                    {
                    m_sound_effect.push_back(tmp_sound_effect);
                    tmp_sound_effect=NULL;
                    }

                tmp_sound_effect = Mix_LoadWAV(m_source_chunk_third.c_str());
                if( tmp_sound_effect == NULL )
                {
                    printf( "Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
                }
                else{
                    m_sound_effect.push_back(tmp_sound_effect);
                    tmp_sound_effect=NULL;
                    }
                Mix_FreeChunk( tmp_sound_effect );
                cout<<"end reading sound effect"<<endl;
            }
            m_vector_size=int(m_sound_effect.size());
    }
    else
        {
            printf( "ERROR reading file \n");
        }

   // m_backup_music = Mix_LoadMUS( "media/The Legion - allegro + reprise.wav" );
    //m_backup_sound=Mix_LoadWAV("media/backup_sound");
    m_vector_size=3;
    m_read_file.close();
    srand (time(NULL));
    m_vector_index=rand() % m_vector_size;
    m_prev_sound=m_vector_index;

    cout<<"vector size"<<m_vector_size<<endl;
    cout<<m_vector_index<<endl;
    printf( "opened Music");
}
void Sound::BackgroundMusic()
{
    printf( "play background music");
    if(m_music[m_vector_index]!=NULL)
    {
        Mix_PlayMusic(m_music[m_vector_index], -1);
    }
    else
        Mix_PlayMusic(m_backup_music, -1);
    if(m_prev_sound!=m_vector_index)
    {
        m_vector_index=rand() % int(m_sound_effect.size());
        m_prev_sound=m_vector_index;
    }


    printf( "played music");
}

void Sound::Sound_Effect()
{
    if(m_sound_effect[m_vector_index]!=NULL)
    {
        Mix_PlayChannel( 1, m_sound_effect[m_vector_index], 0 );
    }
    else
        Mix_PlayChannel( 1, m_backup_sound, 0 );
    m_prev_sound=m_vector_index;
    m_vector_index=rand() % int(m_sound_effect.size());
    if(m_prev_sound==m_vector_index)
    {
        m_vector_index++;
        if(m_vector_index==m_vector_size)
        {
            m_vector_index=0;
        }

    }

}

void Sound::Engine_Sound(bool more)
{
    if(more==true)
    {
        if(m_sound_effect[m_vector_index]!=NULL)
        {
            Mix_PlayChannel( 2, m_sound_effect[m_vector_index], 0 );
        }
        else
            Mix_PlayChannel( 2, m_backup_sound, 0 );

    }
}
void Sound::Play(bool more)
{
    if(m_sound_type=="music")
    {
        BackgroundMusic();
    }
    else
        if(m_sound_type=="sound effect")
        {
            Sound_Effect();
        }
        else
            if(m_sound_type=="engine sound")
            {
                Engine_Sound(more);
            }
}
