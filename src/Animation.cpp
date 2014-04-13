#include "Animation.h"

Animation::Animation(){
    m_width = 0;
    m_height = 0;
    m_source = "";
    m_flip="";
    m_frames_x = 0;
    m_frames_y = 0;
    m_position=0;
    m_frame_duration = 0;
    m_animation_type = "";
    m_startTime = 0;
    m_currentTime = 0;

    img_height=0;
    img_width=0;
    rand_index=0;
    percentage_height=0;
    prev_percentage=0;

    vector_index=0;

    m_repeat_from_index=0;

    flip = SDL_FLIP_NONE;

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
        //if((tmp[i]>='A')&&(tmp[i]<='Z'))
        //{
            tmp[i]=(tolower(tmp[i]));
        //}
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
    m_read_file.open(source.c_str());
    if(m_read_file.is_open())
    {
        m_source = Read_Data(delimiter, "file");
        m_frames_x = To_int(Read_Data(delimiter, "frames x"));
        m_frames_y = To_int(Read_Data(delimiter, "frames y"));
        m_frame_duration = To_int(Read_Data(delimiter, "frame duration"));
        //m_repeat_from_index = To_int(Read_Data(delimiter, "framerestart"));
        m_animation_type = Read_Data(delimiter, "animation type");
        m_flip=Read_Data(delimiter, "flip");
        if((m_animation_type=="hpship")||(m_animation_type=="hpbarbody"))
        {
            m_position=To_int(Read_Data(delimiter, "position"));
        }
        else
            {
                m_position=0;
            }
        m_read_file.close();
    }
    else
    {
        m_source="media/test.png";
        m_frames_x=1;
        m_frames_y=1;
        m_frame_duration=0;
        m_animation_type="";
        m_flip="none";
    }

    cout<<m_source<<endl;
    cout<<m_frames_x<<endl;
    cout<<m_frames_y<<endl;
    cout<<m_frame_duration<<endl;
    cout<<m_animation_type<<endl;
    cout<<m_flip<<endl;


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
        Frames.w=(m_width/m_frames_x);
        Frames.h=(m_height/m_frames_y);

        img_width=m_width/m_frames_x;
        img_height=m_height/m_frames_y;
        percentage_height=Frames.h;
        prev_percentage=100;

        for(Frames.y =0; Frames.y<m_height; Frames.y=Frames.y+m_height/m_frames_y)
        {
            for(Frames.x=0; Frames.x<m_width; Frames.x=Frames.x+m_width/m_frames_x)
            {
                Vector_Frames.push_back(Frames);
            }
        }

        vector_index=0;
        m_startTime=SDL_GetTicks();

        if(m_animation_type=="rand")
        {
            srand (time(NULL));
        }
        if("horizontal"==m_flip)
        {
            flip=SDL_FLIP_HORIZONTAL;
        }
        else
            if("vertical"==m_flip)
        {
            flip=SDL_FLIP_VERTICAL;
        }
        else
            if(m_flip=="none")
        {
            flip=SDL_FLIP_NONE;
        }


}

void Animation::LOOP(int x, int y, int angle, bool m_more, SDL_Renderer* render)
{
    SDL_Rect Destination{x, y, int(m_width/m_frames_x), int(m_height/m_frames_y)};

        m_currentTime=SDL_GetTicks();

        SDL_RenderCopyEx(render,m_Sprite,&Vector_Frames[vector_index],&Destination,angle,NULL,SDL_FLIP_NONE);
        if(m_currentTime - m_startTime >= m_frame_duration)
        {
            vector_index++;
                if(unsigned(vector_index) == Vector_Frames.size())
                {
                    vector_index=0;
                }
                m_startTime = m_currentTime;
        }
}

void Animation::Background(int x, int y, int angle,  bool m_more, SDL_Renderer* render)
{
    SDL_Rect Destination= {x, y, int(m_width/m_frames_x), int(m_height/m_frames_y)};
    SDL_RenderCopyEx(render,m_Sprite,&Vector_Frames[vector_index],&Destination,angle,NULL,SDL_FLIP_NONE);
}

void Animation::Linear(int x, int y, int angle,  bool m_more, SDL_Renderer* render)
{

    if((unsigned(vector_index)!=Vector_Frames.size())&&(m_more==true))
        {

                    SDL_Rect Destination{x, y, int(m_width/m_frames_x), int(m_height/m_frames_y)};

                    m_currentTime=SDL_GetTicks();

                    SDL_RenderCopyEx(render,m_Sprite,&Vector_Frames[vector_index],&Destination,angle,NULL,SDL_FLIP_NONE);
                    if(m_currentTime - m_startTime >= m_frame_duration)
                    {
                        vector_index++;
                        m_startTime = m_currentTime;

                    }
        }
        else
            if(m_more==false)
            {
                vector_index=0;
            }

}

void Animation::Repeat_middle(int x, int y, int angle, bool m_more, SDL_Renderer* render)
{
    if(m_more==true)
    {



        SDL_Rect Destination{x, y, int(m_width/m_frames_x), int(m_height/m_frames_y)};

        m_currentTime=SDL_GetTicks();

        SDL_RenderCopyEx(render,m_Sprite,&Vector_Frames[vector_index],&Destination,angle,NULL,SDL_FLIP_NONE);
        if(m_currentTime - m_startTime >= m_frame_duration)
            {
                if(unsigned(vector_index)==Vector_Frames.size())
                {
                    vector_index=m_repeat_from_index;

                }
                vector_index++;
                m_startTime = m_currentTime;

            }
    }
    else
        if(m_more==false)
        {
            vector_index=0;
        }
}
void Animation::Return_end(int x, int y, int angle, bool m_more, SDL_Renderer* render)
{
    if(m_more==true)
    {
        SDL_Rect Destination{x, y, int(m_width/m_frames_x), int(m_height/m_frames_y)};

        m_currentTime=SDL_GetTicks();

        SDL_RenderCopyEx(render,m_Sprite,&Vector_Frames[vector_index],&Destination,angle,NULL,SDL_FLIP_NONE);
        if(m_currentTime - m_startTime >= m_frame_duration)
        {
            if(m_return==false)
            {
                vector_index++;
            }
            else
                if(m_return==true)
                {
                    vector_index--;
                }

            if(unsigned(vector_index) == Vector_Frames.size())
            {
                vector_index--;
                m_return=true;
            }
            else
                if(vector_index == 0)
                {
                    m_return=false;
                }
            m_startTime = m_currentTime;
        }
    }
    else
        if(m_more==false)
        {
            vector_index = 0;
        }
}
void Animation::Random(int x, int y, int angle, bool m_more, SDL_Renderer* render)
{
    SDL_Rect Destination{x, y, int(m_width/m_frames_x), int(m_height/m_frames_y)};
    m_currentTime=SDL_GetTicks();


    SDL_RenderCopyEx(render,m_Sprite,&Vector_Frames[vector_index],&Destination,angle,NULL,SDL_FLIP_NONE);
    if(m_currentTime - m_startTime >= m_frame_duration)
        {
            vector_index=rand_index;

            m_startTime = rand() % int(m_frames_x*m_frames_y);
        }


}


void Animation::HP_Bar_body(int x, int y, int angle, bool m_more, SDL_Renderer* render)
{
    SDL_Rect Destination{x, y, int(m_width/m_frames_x), int(m_height/m_frames_y)};
    SDL_RenderCopyEx(render,m_Sprite,&Vector_Frames[m_position],&Destination,angle,NULL,flip);
}
void Animation::HP_Bar(int x, int y, int angle,  int percentage,bool m_more, SDL_Renderer* render)
{
    if(prev_percentage!=percentage)
    {
        prev_percentage=percentage;
        percentage_height=int(((percentage_height)*percentage)/100);
        Vector_Frames[m_position].h=percentage_height;
    }

    SDL_Rect Destination2{x, y, int(m_width/m_frames_x), int(percentage_height)};
    SDL_RenderCopyEx(render,m_Sprite,&Vector_Frames[m_position],&Destination2,angle,NULL,flip);
}


void Animation::Draw(int x, int y, int angle, bool m_more, SDL_Renderer* render)
{
    if(m_animation_type=="background")
    {
        Background(x, y, angle, m_more,render);
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
                    else
                    if(m_animation_type=="random")
                    {
                        Random(x, y, angle, m_more, render);
                    }
                    else
                        if(m_animation_type=="hpbarbody")
                        {
                            HP_Bar_body(x, y, angle, m_more, render);
                        }
}
