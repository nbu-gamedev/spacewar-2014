#include "Animation.h"

Animation::Animation(){
    m_width = 0;
    m_height = 0;
    m_frames_x = 0;
    m_frames_y = 0;
    m_position=0;
    m_startTime = 0;
    m_currentTime = 0;
    m_frame_duration = 0;
    g_img_height=0;
    g_img_width=0;
    m_rand_index=0;
    m_percentage_height=0;
    m_prev_percentage=0;
    m_vector_index=0;
    m_repeat_from_index=0;
    m_repetition_searching_var=0;
    m_row_elements = 0;
    m_column_num = 0;
    m_angle=0;

    m_source = "";
    m_flip_type="";
    m_animation_type = "";

    m_return=false;

    m_flip = SDL_FLIP_NONE;

    m_file = NULL;
    m_sprite = NULL;
}

Animation::~Animation()
{
    SDL_DestroyTexture(m_sprite);
    printf("Destroyed Animation Objects!!!\n");
}

string Animation::delSpace(string &tmp_str)
{
    while(' ' == tmp_str[0] && 0<tmp_str.length()) tmp_str.erase(tmp_str.begin());
    while(' ' == tmp_str[tmp_str.length()-1] && 0<tmp_str.length()) tmp_str.erase(tmp_str.end()-1);

    return tmp_str;
}

string Animation::deCaps(string tmp)
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

int Animation::To_int(string tmp)
{
    int numbre=0;
    if ('0' <= tmp[0] && tmp[0] <= '9')
        {
            numbre=atoi(tmp.c_str());
            tmp="";
        }
    return numbre;
}


string Animation::Read_Data(string delimiter, string prefix)
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



void Animation::Init(SDL_Renderer* render, string source)
{
    string delimiter = ":";
    m_read_file.open(source);
    if(m_read_file.is_open())
    {
        m_source = Read_Data(delimiter, "file");
        m_frames_x = To_int(Read_Data(delimiter, "frames x"));
        m_frames_y = To_int(Read_Data(delimiter, "frames y"));
        m_frame_duration = To_int(Read_Data(delimiter, "frame duration"));
        m_animation_type = Read_Data(delimiter, "animation type");
        m_flip_type=Read_Data(delimiter, "flip");
        g_img_width=To_int(Read_Data(delimiter, "width"));
        g_img_height=To_int(Read_Data(delimiter, "height"));

        if((m_animation_type=="hpship")||(m_animation_type=="hpbarbody"))
        {
            m_position=To_int(Read_Data(delimiter, "position"));
        }
        else
        {
            m_position=0;
        }
        if(m_animation_type=="repeat middle")
        {
            m_repeat_from_index=To_int(Read_Data(delimiter, "repeat from"));
        }
        else
        {
            m_repeat_from_index=int(m_frames_x/2);
        }
        m_read_file.close();
    }
    else
    {
        m_source="media/Magenta.png";
        m_frames_x=1;
        m_frames_y=1;
        m_frame_duration=0;
        m_animation_type="";
        m_flip_type="none";
    }

    if("horizontal"==m_flip_type)
        {
            m_flip=SDL_FLIP_HORIZONTAL;
        }
        else
            if("vertical"==m_flip_type)
            {
                m_flip=SDL_FLIP_VERTICAL;
            }
            else
                m_flip=SDL_FLIP_NONE;

    if(m_animation_type=="rand")
        {
            srand (time(NULL));
        }

    m_file = IMG_Load(m_source.c_str());

    if(m_sprite != NULL)
    {
        SDL_DestroyTexture(m_sprite);
    }
        if(m_file == NULL)
        {
            printf("ERROR opening image : %s , SDL_Eror: %s\n",(char*)m_source.c_str(),SDL_GetError());
        }
        else
        {
            m_sprite = SDL_CreateTextureFromSurface(render,m_file);
            if(m_sprite == NULL)
            {
                printf("ERROR Creating Texture from : %s , SDL_Eror: %s\n",(char*)m_source.c_str(),SDL_GetError());
            }
            else
            {
                m_width = m_file->w;
                m_height = m_file->h;
            }
            SDL_FreeSurface(m_file);
        }

        SDL_Rect Frames;
        Frames.x=0;
        Frames.y=0;
        Frames.w=int(m_width/m_frames_x);
        Frames.h=int(m_height/m_frames_y);

        m_percentage_height=Frames.h;

        m_prev_percentage=100;
        m_vector_index=0;
        m_startTime=SDL_GetTicks();

        for(Frames.y =0; Frames.y<m_height; Frames.y=Frames.y+m_height/m_frames_y)
        {
            for(Frames.x=0; Frames.x<m_width; Frames.x=Frames.x+m_width/m_frames_x)
            {
                m_vector_frames.push_back(Frames);
            }
        }
}

void Animation::LOOP(int x, int y, int angle, bool more, SDL_Renderer* render)
{
    SDL_Rect Destination{x, y, g_img_width, g_img_height};

        m_currentTime=SDL_GetTicks();

        SDL_RenderCopyEx(render,m_sprite,&m_vector_frames[m_vector_index],&Destination,angle,NULL,m_flip);
        if(m_currentTime - m_startTime >= m_frame_duration)
        {
            m_vector_index++;
                if(unsigned(m_vector_index) == m_vector_frames.size())
                {
                    m_vector_index=0;
                }
            m_startTime = m_currentTime;
        }
}

void Animation::Background(int x, int y, int angle,  bool more, SDL_Renderer* render)
{
    SDL_Rect Destination= {x, y, int(m_width/m_frames_x), int(m_height/m_frames_y)};
    SDL_RenderCopyEx(render,m_sprite,&m_vector_frames[m_vector_index],&Destination,angle,NULL,m_flip);
}

void Animation::Linear(int x, int y, int angle,  bool more, SDL_Renderer* render)
{
    if((unsigned(m_vector_index)!=m_vector_frames.size())&&(more==true))
    {
        m_currentTime=SDL_GetTicks();
        SDL_Rect Destination{x, y, g_img_width, g_img_height};
        SDL_RenderCopyEx(render,m_sprite,&m_vector_frames[m_vector_index],&Destination,angle,NULL,m_flip);

        if(m_currentTime - m_startTime >= m_frame_duration)
        {
            m_vector_index++;
            m_startTime = m_currentTime;
        }
    }
    else
        if(more==false)
        {
            m_vector_index=0;
        }
}

void Animation::Repeat_middle(int x, int y, int angle, bool more, SDL_Renderer* render)
{
    if(more==true)
    {
        if(unsigned(m_vector_index)==m_vector_frames.size())
            {
                m_vector_index=m_repeat_from_index;
            }
        m_currentTime=SDL_GetTicks();
        SDL_Rect Destination{x, y, g_img_width, g_img_height};
        SDL_RenderCopyEx(render,m_sprite,&m_vector_frames[m_vector_index],&Destination,angle,NULL,m_flip);

        if(m_currentTime - m_startTime >= m_frame_duration)
        {


            m_vector_index++;
            m_startTime = m_currentTime;
        }
    }
    else
        m_vector_index=0;

}
void Animation::Return_end(int x, int y, int angle, bool more, SDL_Renderer* render)
{
    if(more==true)
    {
        m_currentTime=SDL_GetTicks();
        SDL_Rect Destination{x, y, g_img_width, g_img_height};
        SDL_RenderCopyEx(render,m_sprite,&m_vector_frames[m_vector_index],&Destination,angle,NULL,m_flip);

        if(m_currentTime - m_startTime >= m_frame_duration)
        {
            if(m_return==false)
            {
                m_vector_index++;
            }
            else
                if(m_return==true)
                {
                    m_vector_index--;
                }

            if(unsigned(m_vector_index) == m_vector_frames.size())
            {
                m_vector_index--;
                m_return=true;
            }
            else
                if(m_vector_index == 0)
                {
                    m_return=false;
                }
            m_startTime = m_currentTime;
        }
    }
    else
        m_vector_index = 0;

}
void Animation::Random(int x, int y, int angle, bool more, SDL_Renderer* render)
{
    m_currentTime=SDL_GetTicks();
    SDL_Rect Destination{x, y, g_img_width, g_img_height};
    SDL_RenderCopyEx(render,m_sprite,&m_vector_frames[m_vector_index],&Destination,angle,NULL,m_flip);

    if(m_currentTime - m_startTime >= m_frame_duration)
        {
            m_vector_index=rand() % int(m_frames_x*m_frames_y);
            m_startTime = m_currentTime;
        }
}


void Animation::HP_Bar_body(int x, int y, int angle, bool more, SDL_Renderer* render)
{
    SDL_Rect Destination{x, y, g_img_width, g_img_height};
    SDL_RenderCopyEx(render,m_sprite,&m_vector_frames[m_position],&Destination,angle,NULL,m_flip);
}
void Animation::HP_Bar(int x, int y, int angle,  int percentage,bool more, SDL_Renderer* render)
{
    if(m_prev_percentage!=percentage)
    {
        m_prev_percentage=percentage;
        m_percentage_height=int(((g_img_height)*percentage)/100);
        m_vector_frames[m_position].h=m_percentage_height;
    }

    SDL_Rect Destination2{x, y, g_img_width, m_percentage_height};
    SDL_RenderCopyEx(render,m_sprite,&m_vector_frames[m_position],&Destination2,angle,NULL,m_flip);
}

void Animation::Button (int x, int y, int index, SDL_Renderer* render)
{
    SDL_Rect Destination{x, y, g_img_width, g_img_height};
    SDL_RenderCopyEx(render,m_sprite,&m_vector_frames[index],&Destination,0,NULL,m_flip);
}

void Animation::Draw_Image(int x, int y, int angle, bool more, SDL_Renderer* render)
{

    SDL_Rect Destination{x, y, g_img_width, g_img_height};
    SDL_RenderCopyEx(render,m_sprite,&m_vector_frames[0],&Destination,m_angle,NULL,m_flip);
    m_angle=(m_angle+angle)%360;
}

void Animation::Draw(int x, int y, int angle, bool more, SDL_Renderer* render)
{
    if(m_animation_type=="background")
    {
        Background(x, y, angle, more,render);
    }
    else
        if(m_animation_type=="loop")
        {
            LOOP(x, y, angle, more, render);
        }
        else
            if(m_animation_type=="linear")
            {
                Linear(x, y, angle, more, render);
            }
            else
                if(m_animation_type=="repeat middle")
                {
                    Repeat_middle(x, y, angle, more, render);
                }
                else
                    if(m_animation_type=="return from end")
                    {
                        Return_end(x, y, angle, more, render);
                    }
                    else
                    if(m_animation_type=="random")
                    {
                        Random(x, y, angle, more, render);
                    }
                    else
                        if(m_animation_type=="hpbarbody")
                        {
                            HP_Bar_body(x, y, angle, more, render);
                        }
                        else
                            if(m_animation_type=="draw image")
                            {
                                Draw_Image(x, y, angle, more, render);
                            }
}
