#pragma once

#include <math.h>

class Vector2D
{
public:
    Vector2D(float x, float y) : m_x(x), m_y(y)
    {
    }

    inline float GetX() { return m_x; }
    inline float GetY() { return m_y; }
    inline void SetX(float x) { m_x = x; }
    inline void SetY(float y) { m_y = y; }

    float Length();
    void Normalize();

    // operators
    Vector2D operator+(const Vector2D& other) const;
    Vector2D operator*(float scalar);
    Vector2D& operator*=(float scalar);
    Vector2D operator-(const Vector2D& other) const;
    Vector2D operator/(float scalar);
    Vector2D& operator/=(float scalar);

    friend Vector2D& operator+=(Vector2D& v1, const Vector2D& v2);
    friend Vector2D& operator-=(Vector2D& v1, const Vector2D& v2);

private:
    float m_x;
    float m_y;
};