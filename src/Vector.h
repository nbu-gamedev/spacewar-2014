#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED
#include <stdio.h>
#include <math.h>
#define PI 3.14159265

class Vector
{
public:
    float m_x;
    float m_y;

    Vector();
    Vector(float x,float y);
    void SetXY(float x,float y);

    Vector& operator +=(const Vector& Ve2);
    Vector& operator -=(const Vector& Ve2);
    Vector& operator *=(const Vector& Ve2);
    Vector& operator /=(const Vector& Ve2);

    Vector operator+(const Vector& Ve2)const;
    Vector operator-(const Vector& Ve2)const;
    Vector operator*(const Vector& Ve2)const;

    Vector& operator=(const Vector& Ve2);

    bool operator==(const Vector& Ve2);
    bool operator!=(const Vector& Ve2);

    Vector& operator*=(const float scalar);
    Vector& operator/=(const float scalar);

    const Vector operator*(const float scalar);
    const Vector operator/(const float scalar);

    void Rotate(const float angle);
    float Length();
};

#endif // VECTOR_H_INCLUDED
