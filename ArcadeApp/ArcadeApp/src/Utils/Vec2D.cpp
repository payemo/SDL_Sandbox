#include "Vec2D.h"
#include "Utils.h"
#include <cassert>

const Vec2D Vec2D::Zero;

bool Vec2D::operator==(const Vec2D& other) const
{
	return Equals(this->mX, other.mX) && Equals(this->mY, other.mY);
}

bool Vec2D::operator!=(const Vec2D& other) const
{
	return !(*this == other);
}

Vec2D Vec2D::operator-() const
{
	return Vec2D(-mX, -mY);
}

Vec2D Vec2D::operator*(float scale) const
{
	return Vec2D(mX * scale, mY * scale);
}

Vec2D Vec2D::operator/(float scale) const
{
	assert(fabsf(scale) > EPSILON);
	return Vec2D(mX / scale, mY / scale);
}

Vec2D& Vec2D::operator*=(float scale)
{
	*this = *this * scale;
	return *this;
}

Vec2D& Vec2D::operator/=(float scale)
{
	assert(fabsf(scale) > EPSILON);

	*this = *this / scale;
	return *this;
}

Vec2D operator*(float scale, const Vec2D& vec)
{
	return vec * scale;
}

Vec2D Vec2D::operator+(const Vec2D& vec) const
{
	return Vec2D(mX + vec.mX, mY + vec.mY);
}

Vec2D Vec2D::operator-(const Vec2D& vec) const
{
	return Vec2D(mX - vec.mX, mY - vec.mY);
}

Vec2D& Vec2D::operator+=(const Vec2D& vec)
{
	*this = *this + vec;
	return *this;
}

Vec2D& Vec2D::operator-= (const Vec2D& vec)
{
	*this = *this - vec;
	return *this;
}

float Vec2D::Mag() const
{
	return std::sqrt(Mag2());
}

float Vec2D::Mag2() const
{
	return Dot(*this);
}

Vec2D Vec2D::GetUnitVec() const
{
	float m = Mag();

	if (m > EPSILON)
	{
		return *this / m;
	}

	return Vec2D::Zero;
}

Vec2D& Vec2D::Normalize()
{
	float m = Mag();

	if (m > EPSILON)
	{
		*this /= m;
	}

	return *this;
}

float Vec2D::Distance(const Vec2D& vec) const
{
	return (*this - vec).Mag();
}

float Vec2D::Dot(const Vec2D& vec) const
{
	return mX * vec.mX + mY * vec.mY;
}


Vec2D Vec2D::ProjectOnto(const Vec2D& vec2) const
{
	Vec2D unitVec2 = vec2.GetUnitVec();
	float dot = Dot(unitVec2);
	return unitVec2 * dot;
}

float Vec2D::Angle(const Vec2D& vec2) const
{
	return std::acosf(GetUnitVec().Dot(vec2.GetUnitVec()));
}

Vec2D Vec2D::Reflect(const Vec2D& normal) const
{
	// v - 2 * (v * n) * n,
	// where n - normalized vector, v * n - scalar product
	return *this - 2 * ProjectOnto(normal);
}

void Vec2D::Rotate(float angle, const Vec2D& aroundPoint)
{
	float cos = std::cosf(angle);
	float sin = std::sinf(angle);
	Vec2D thisVec(mX, mY);

	thisVec -= aroundPoint;

	float xRot = thisVec.mX * cos - thisVec.mY * sin;
	float yRot = thisVec.mX * sin + thisVec.mY * cos;

	Vec2D rot = Vec2D(xRot, yRot);
	*this = rot + aroundPoint;
}

Vec2D Vec2D::RotationResult(float angle, Vec2D& aroundPoint) const
{
	float cos = std::cosf(angle), sin = std::sinf(angle);
	Vec2D thisVec(mX, mY);

	thisVec -= aroundPoint;

	float xRot = thisVec.mX * cos - thisVec.mY * sin;
	float yRot = thisVec.mX * sin + thisVec.mY * cos;

	Vec2D rot = Vec2D(xRot, yRot);
	return rot + aroundPoint;
}

std::ostream& operator<<(std::ostream& os, const Vec2D& vec)
{
	std::cout << "X: " << vec.mX << "; " << "Y: " << vec.mY << std::endl;
	return os;
}