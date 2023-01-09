#pragma once

#include <iostream>
#include "Utils.h"

using namespace Utils;

class Vec2D
{
public:
	static const Vec2D Zero;

	Vec2D() : Vec2D(0, 0) {}
	Vec2D(float x, float y) : mX(x), mY(y) {}

	inline void SetX(float x) { mX = x; }
	inline void SetY(float y) { mY = y; }
	inline float GetX() const { return mX; }
	inline float GetY() const { return mY; }

	float Mag() const;
	float Mag2() const;

	float Distance(const Vec2D& vec) const;
	float Dot(const Vec2D& vec) const;

	Vec2D GetUnitVec() const;
	Vec2D& Normalize(); 

	bool operator==(const Vec2D& other) const;
	bool operator!=(const Vec2D& other) const;
	Vec2D operator-() const;
	Vec2D operator*(float scale) const;
	Vec2D operator/(float scale) const;
	Vec2D& operator*=(float scale);
	Vec2D& operator/=(float scale);

	Vec2D operator+(const Vec2D& vec) const;
	Vec2D operator-(const Vec2D& vec) const;
	Vec2D& operator+=(const Vec2D& vec);
	Vec2D& operator-= (const Vec2D & vec);

	friend Vec2D operator*(float scale, const Vec2D& vec);

	friend std::ostream& operator<<(std::ostream& os, const Vec2D& value);

private:
	float mX;
	float mY;
};