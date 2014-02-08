#include "World.h" // defines class World
#include <stdio.h>
#include "SDL_image.h"

World::World()//class World constructor
{
    Texture=NULL;
    Width=0;
    Height=0;
};

World::~World()//class World destructor
{
    Destroy_texture();//destroy the texture
};

void World::Destroy_texture()//Function for destroying the texture
{
    if(Texture!=NULL)//check if the texture is empty
    {
        SDL_DestroyTexture(Texture);// clear the old texture
    }
};

bool World::LoadFile(char* destination,SDL_Renderer* render)
{
    Destroy_texture();

        SDL_Texture* avr_Texture = NULL;//define empty temporary texture
        SDL_Surface* File = IMG_Load(destination);//open the file of the image

        if(File == NULL)//check if file is open correctly
        {
            printf("ERROR opening image : %s , SDL_Eror: %s\n",destination,SDL_GetError());
        }
        else
        {
            avr_Texture = SDL_CreateTextureFromSurface(render,File);//
            if(avr_Texture == NULL)//check if the temporary texture is empty
            {
                printf("ERROR Creating Texture from : %s , SDL_Eror: %s\n",destination,SDL_GetError());
            }
            else
            {
                Width = File->w;//set value for Width
                Height = File->h;//set value for Height
            }
            SDL_FreeSurface(File);//Clear the pointer to the File
        }
        Texture = avr_Texture;//copy the avr_Texture to Texture
        return Texture!=NULL;//Check if the Texture is empty
                            //if it is empty return false else return true
}

void World::Visualization(int avr_x,int avr_y,double angle,SDL_RendererFlip Flip_img,SDL_Renderer* render)//
{
        Wx = avr_x;
        Wy = avr_y;
        SDL_Rect position;
        position.x = avr_x;
        position.y = avr_y;
        position.w = Width;
        position.h = Height;

        SDL_RenderCopyEx(render,Texture,NULL,&position,angle,NULL,Flip_img);
        //SDL_RenderCopy(render,Texture,NULL,&position);
};

int World::GetWidth()//returns the width of image
{
    return Width;
};

int World::GetHeight()//returns the height of image
{
    return Height;
};

int World::GetX()
{
    return Wx;
}

int World::GetY()
{
    return Wy;
}
