#include "Vector2D.h"

float Vector2D::Length()
{
    return sqrt(m_x * m_x + m_y * m_y);
}

void Vector2D::Normalize()
{
    float l = Length();

    if (l > 0) {
        (*this) *= (1 / l);
    }
}

// Operators

Vector2D Vector2D::operator+(const Vector2D& other) const
{
    return Vector2D(m_x + other.m_x, m_y + other.m_y);
}

Vector2D Vector2D::operator*(float scalar)
{
    return Vector2D(m_x * scalar, m_y * scalar);
}

Vector2D& Vector2D::operator*=(float scalar)
{
    m_x *= scalar;
    m_y *= scalar;

    return *this;
}

Vector2D& operator+=(Vector2D& v1, const Vector2D& v2)
{
    v1.m_x += v2.m_x;
    v1.m_y += v2.m_y;
    return v1;
}

Vector2D Vector2D::operator-(const Vector2D& other) const
{
    return Vector2D(m_x - other.m_x, m_y - other.m_y);
}

Vector2D& operator-=(Vector2D& v1, const Vector2D& v2)
{
    v1.m_x -= v2.m_x;
    v1.m_y -= v2.m_y;
    return v1;
}

Vector2D Vector2D::operator/(float scalar)
{
    return Vector2D(m_x / scalar, m_y / scalar);
}

Vector2D& Vector2D::operator/=(float scalar)
{
    m_x /= scalar;
    m_y /= scalar;

    return *this;
}