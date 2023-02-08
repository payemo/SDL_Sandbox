#pragma once
#include <cmath>

namespace Utils
{
	static const float EPSILON = 0.0001f;

	const float PI = 3.14159f;
	const float TWO_PI = 2.f * PI;

	inline bool Equals(float a, float b)
	{
		return fabsf(a - b) < EPSILON;
	}

	inline bool GreaterThanOrEqual(float a, float b)
	{
		return (a > b) || Equals(a, b);
	}

	inline bool LessThanOrEqual(float a, float b)
	{
		return !GreaterThanOrEqual(a, b);
	}
}