#include "Vector.h"

Vector::Vector(){
    m_x = 0;
    m_y = 0;
};

Vector::Vector(float x,float y){
    m_x = x;
    m_y = y;
}

void Vector::SetXY(float x,float y){
    m_x = x;
    m_y = y;
}

 Vector& Vector::operator +=(const Vector& Ve2){
    m_x += Ve2.m_x;
    m_y += Ve2.m_y;
    return (*this);
}

 Vector& Vector::operator -=(const Vector& Ve2){
    m_x -= Ve2.m_x;
    m_y -= Ve2.m_y;
    return (*this);
}

Vector& Vector::operator *=(const Vector& Ve2){
    m_x *= Ve2.m_x;
    m_y *= Ve2.m_y;
    return (*this);
}

Vector& Vector::operator /=(const Vector& Ve2){
    m_x /= Ve2.m_x;
    m_y /= Ve2.m_y;
    return (*this);
}

Vector Vector::operator+(const Vector& Ve2)const{
    return Vector(*this) += Ve2;
}

Vector Vector::operator-(const Vector& Ve2)const{
    return Vector(*this) -= Ve2;
}

bool Vector::operator==(const Vector& Ve2){

    return ((m_x == Ve2.m_x)&&(m_y = Ve2.m_y));
}

bool Vector::operator!=(const Vector& Ve2){

    return !((m_x == Ve2.m_x)&&(m_y = Ve2.m_y));
}

Vector& Vector::operator=(const Vector& Ve2){
    m_x = Ve2.m_x;
    m_y = Ve2.m_y;
    return *this;
}

Vector Vector::operator*(const Vector& Ve2)const{
    return (Vector(m_x*Ve2.m_x,m_y*Ve2.m_y));
}

Vector& Vector::operator*=(const float scalar){
    m_x *= scalar;
    m_y *= scalar;
    return *this;
}

Vector& Vector::operator/=(const float scalar){
    m_x /= scalar;
    m_y /= scalar;
    return *this;
}

const Vector Vector::operator*(const float scalar){
    return Vector(*this) *= scalar;
}

const Vector Vector::operator/(const float scalar){
    return Vector(*this) /= scalar;
}

Vector& Vector::operator+(const float scalar)
{
    m_x += scalar;
    m_y += scalar;
    return *this;
}

Vector& Vector::operator-(const float scalar)
{
    m_x -= scalar;
    m_y -= scalar;
    return *this;
}

void Vector::Rotate(const float angle){
    float x = cos(angle*PI/180);
    float y = sin(angle*PI/180);

    m_x = x;
    m_y = y;
}

void Vector::ChangeAngle(const float angle){
    float x = acos(angle*PI/180);
    float y = asin(angle*PI/180);

    m_x = x;
    m_y = y;
}

float Vector::Length(){
    float length;
    length = sqrt((m_x*m_x) + (m_y*m_y));
    return length;
}

float Vector::DotProduction(Vector other)
{
    return (m_x * other.m_x) + (m_y * other.m_y);
}

float Vector::CollisionAngle (Vector other)
{
   /* if(other.m_x == 1.0f || other.m_x == -1.0f)
    {
        return asin(m_y)*180/PI;
    }
    else
    if(other.m_y == 1.0f || other.m_y == -1.0f)
    {
       return acos(m_x)*180/PI;
    }
    */
    return atan2(m_x,m_y)*180/PI;
}



