#include "Animation.h"

Animation::Animation(){
    m_width = 0;
    m_height = 0;
    m_source = "";
    m_frames_x = 0;
    m_frames_y = 0;
    m_frame_duration = 0;
    m_animation_type = "";
    m_startTime = 0;
    m_currentTime = 0;
    img_height=0;
    img_width=0;

    m_return=false;

    repetition_searching_var=0;
    m_row_elements = 0;
    m_column_num = 0;

    File = NULL;
    m_Sprite = NULL;
};

Animation::~Animation()
{
    SDL_DestroyTexture(m_Sprite);
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
    while((more)&&(getline(m_read_file, tmp)))
    {
        repetition_searching_var++;
        data=deCaps(tmp.substr(0, tmp.find(delimiter)));
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
                more=false;

            }
    }
    if(repetition_searching_var>1)
    {
        m_read_file.clear();
        m_read_file.seekg(0, ios_base::beg);
        repetition_searching_var=0;
    }
    else
        data="";
    return data;
}

void Animation::Init(SDL_Renderer* render, string source)
{
    string delimiter = ":";
    m_read_file.open(source.c_str());
    if(m_read_file.is_open())
    {
        m_source = Read_Data(delimiter, "file");
        m_frames_x = To_int(Read_Data(delimiter, "frames x"));
        m_frames_y = To_int(Read_Data(delimiter, "frames y"));
        m_frame_duration = To_int(Read_Data(delimiter, "frame duration"));
        m_animation_type = Read_Data(delimiter, "animation type");
        m_read_file.close();
    }
    else
    {
        m_source="media/test.png";
        m_frames_x=1;
        m_frames_y=1;
        m_frame_duration=0;
        m_animation_type="";
    }



    File = IMG_Load(m_source.c_str());
    if(m_Sprite != NULL)
    {
        SDL_DestroyTexture(m_Sprite);
    }
        if(File == NULL)
        {
            printf("ERROR opening image : %s , SDL_Eror: %s\n",(char*)m_source.c_str(),SDL_GetError());
        }
        else
        {
            m_Sprite = SDL_CreateTextureFromSurface(render,File);
            if(m_Sprite == NULL)
            {
                printf("ERROR Creating Texture from : %s , SDL_Eror: %s\n",(char*)m_source.c_str(),SDL_GetError());
            }
            else
            {
                m_width = File->w;
                m_height = File->h;
            }
            SDL_FreeSurface(File);
        }
        SDL_Rect Frames;
        Frames.x=0;
        Frames.y=0;
        Frames.w=m_width/m_frames_x;
        Frames.h=m_height/m_frames_y;

        img_width=m_width/m_frames_x;
        img_height=m_height/m_frames_y;

        for(Frames.y =0; Frames.y<m_height; Frames.y=Frames.y+m_height/m_frames_y)
        {
            for(Frames.x=0; Frames.x<m_width; Frames.x=Frames.x+m_width/m_frames_x)
            {
                List_Frames.push_back(Frames);
            }
        }
        it=List_Frames.begin();
        m_startTime=SDL_GetTicks();
}

void Animation::LOOP(int x, int y, int angle, bool m_more, SDL_Renderer* render)
{
    SDL_Rect Destination{x, y, m_width/m_frames_x, m_height/m_frames_y};

        m_currentTime=SDL_GetTicks();

        SDL_RenderCopyEx(render,m_Sprite,&*it,&Destination,angle,NULL,SDL_FLIP_NONE);
        if(m_currentTime - m_startTime >= m_frame_duration)
        {
            it++;
                if(it == List_Frames.end())
                {
                    it = List_Frames.begin();
                }
                m_startTime = m_currentTime;
        }
}

void Animation::Background(int x, int y, int angle,  SDL_Renderer* render)
{
    SDL_Rect Destination= {x, y, m_width/m_frames_x, m_height/m_frames_y};
    SDL_RenderCopyEx(render,m_Sprite,&*it,&Destination,angle,NULL,SDL_FLIP_NONE);
}

void Animation::Linear(int x, int y, int angle,  bool m_more, SDL_Renderer* render)
{

    if((it!=List_Frames.end())&&(m_more==true))
        {

                    SDL_Rect Destination{x, y, m_width/m_frames_x, m_height/m_frames_y};

                    m_currentTime=SDL_GetTicks();

                    SDL_RenderCopyEx(render,m_Sprite,&*it,&Destination,angle,NULL,SDL_FLIP_NONE);
                    if(m_currentTime - m_startTime >= m_frame_duration)
                    {
                        it++;
                        m_startTime = m_currentTime;

                    }
        }
        else
            if(m_more==false)
            {
                it = List_Frames.begin();
            }

}

void Animation::Repeat_middle(int x, int y, int angle, bool m_more, SDL_Renderer* render)
{
    if(m_more==true)
    {



        SDL_Rect Destination{x, y, m_width/m_frames_x, m_height/m_frames_y};

        m_currentTime=SDL_GetTicks();

        SDL_RenderCopyEx(render,m_Sprite,&*it,&Destination,angle,NULL,SDL_FLIP_NONE);
        if(m_currentTime - m_startTime >= m_frame_duration)
            {
                if(it==List_Frames.end())
                {
                    it=List_Frames.begin();
                    for(unsigned int i=0; i<(List_Frames.size())/2; i++)
                    {
                        it++;
                    }
                }
                it++;
                m_startTime = m_currentTime;

            }
    }
    else
        if(m_more==false)
        {
            it=List_Frames.begin();
        }
}
void Animation::Return_end(int x, int y, int angle, bool m_more, SDL_Renderer* render)
{
    if(m_more==true)
    {
        SDL_Rect Destination{x, y, m_width/m_frames_x, m_height/m_frames_y};;

        m_currentTime=SDL_GetTicks();

        SDL_RenderCopyEx(render,m_Sprite,&*it,&Destination,angle,NULL,SDL_FLIP_NONE);
        if(m_currentTime - m_startTime >= m_frame_duration)
        {
            if(m_return==false)
            {
                it++;
            }
            else
                if(m_return==true)
                {
                    it--;
                }

            if(it == List_Frames.end())
            {
                it--;
                m_return=true;
            }
            else
                if(it == List_Frames.begin())
                {
                    m_return=false;
                }
            m_startTime = m_currentTime;
        }
    }
    else
        if(m_more==false)
        {
            it == List_Frames.begin();
        }
}
void Animation::Draw(int x, int y, int angle, bool m_more, SDL_Renderer* render)
{
    if(m_animation_type=="background")
    {
        Background(x, y, angle, render);
    }
    else
        if(m_animation_type=="loop")
        {
            LOOP(x, y, angle, m_more, render);
        }
        else
            if(m_animation_type=="linear")
            {
                Linear(x, y, angle, m_more, render);
            }
            else
                if(m_animation_type=="repeat middle")
                {
                    Repeat_middle(x, y, angle, m_more, render);
                }
                else
                    if(m_animation_type=="return from end")
                    {
                        Return_end(x, y, angle, m_more, render);
                    }

}

