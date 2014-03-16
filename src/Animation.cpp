#include "Animation.h"

Animation::Animation(){};

Animation::~Animation()
{
    SDL_DestroyTexture(m_Sprite);
    printf("Destroyed Animation Objects!!!\n");
}
string Animation::delSpace(string &tmp_str)
{
    for(int i = 0; i<=tmp_str.length(); i++)
    {
        for(int q = 0; q <=i; q++)
        {
            if(tmp_str[q] == ' ' && tmp_str[q+1] == ' ')
            {
                tmp_str.erase(tmp_str.begin() + q);
            }
            else if(tmp_str[0]== ' ')
            {
                tmp_str.erase(tmp_str.begin());
            }
            else if(tmp_str[q] == '\0' && tmp_str[q-1]== ' ')
            {
                tmp_str.erase(tmp_str.end() - 1);
            }
        }
    }
    return tmp_str;
}

void Animation::Init(SDL_Renderer* render, string source)
{

    string tmp;
    string delimiter = ":";
    ifstream read_file;

    read_file.open(source.c_str());

    while(!read_file.eof())
    {
        getline(read_file, tmp);
        if(tmp[0]=='/')
        {

        }
        else
        {
            if(tmp.substr(0, tmp.find(delimiter))=="file")
            {
                m_source=tmp.substr((tmp.find(delimiter)+1), tmp.size());
                m_source=delSpace(m_source);
                tmp="";
            }
            else if(tmp.substr(0, tmp.find(delimiter))=="frames x")
                  {
                     tmp=tmp.substr((tmp.find(delimiter)+1), tmp.size());
                     tmp=delSpace(tmp);

                     if ('0' <= tmp[0] && tmp[0] <= '9')
                        {
                            m_frames_x=atoi(tmp.c_str());
                            tmp="";
                        }
                  }
            else if(tmp.substr(0, tmp.find(delimiter))=="frames y")
                  {
                      tmp=tmp.substr((tmp.find(delimiter)+1), tmp.size());
                      tmp=delSpace(tmp);
                      if ('0' <= tmp[0] && tmp[0] <= '9')
                        {
                            m_frames_y=atoi(tmp.c_str());
                            tmp="";
                        }
                  }
            else if(tmp.substr(0, tmp.find(delimiter))=="framerate")
                  {
                      tmp=tmp.substr((tmp.find(delimiter)+1), tmp.size());
                      tmp=delSpace(tmp);

                      if ('0' <= tmp[0] && tmp[0] <= '9')
                        {
                            m_framerate=atoi(tmp.c_str());
                            tmp="";
                        }
                  }
            else if(tmp.substr(0, tmp.find(delimiter))=="loop")
                  {
                      m_loop=tmp.substr((tmp.find(delimiter)+1), tmp.size());
                      m_loop=delSpace(m_loop);
                      tmp="";
                  }
        }
    }
    read_file.close();


    m_Render = render;

    File = IMG_Load(m_source.c_str());

    SDL_DestroyTexture(m_Sprite);

        if(File == NULL)
        {
            printf("ERROR opening image : %s , SDL_Eror: %s\n",(char*)m_source.c_str(),SDL_GetError());
        }
        else
        {
            m_Sprite = SDL_CreateTextureFromSurface(m_Render,File);
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

void Animation::Draw(int x, int y, int angle, bool tmp_bool_var)
{

    m_more=tmp_bool_var;

    SDL_Rect Destination;
    Destination.x = x-(*it).w/2;
    Destination.y = y-(*it).h/2;
    Destination.w = m_width/m_frames_x;
    Destination.h = m_height/m_frames_y;

    m_currentTime=SDL_GetTicks();

    SDL_RenderCopyEx(m_Render,m_Sprite,&*it,&Destination,angle,NULL,SDL_FLIP_NONE);
    if(m_currentTime - m_startTime >= m_framerate)
    {
            it++;
            m_startTime = m_currentTime;
    }

}

