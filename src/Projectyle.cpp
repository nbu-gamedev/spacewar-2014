#include "Projectyle.h"

Projectyle::Projectyle(){}

void Projectyle::Init(Vector heading,Vector cordinates){
    m_live = true;
    m_lifetime = 2000;
    m_startTime = SDL_GetTicks();
    m_cordinates = cordinates;
    m_heading = heading;

}

void Projectyle::Update(){
    m_currentTime = SDL_GetTicks();
    if(m_currentTime - m_startTime >= m_lifetime/1000){

        m_live = false;

    }else{
        m_cordinates += m_heading*m_speed;
    }



}
