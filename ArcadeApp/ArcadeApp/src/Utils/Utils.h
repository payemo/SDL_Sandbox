#pragma once
#include <cmath>
#include <algorithm>
#include <cctype>

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

	inline float MillisecondsToSeconds(unsigned int milliseconds)
	{
		return static_cast<float>(milliseconds) / 1000.0f;
	}

	inline unsigned int Get2DIndex(unsigned int width, unsigned int r, unsigned int c)
	{
		return r * width + c;
	}

	inline bool StringCompare(const std::string& str1, const std::string& str2)
	{
		if (str1.length() == str2.length())
		{
			return std::equal(str1.begin(), str1.end(), str2.begin(), [](unsigned char a, unsigned char b) {
				return std::tolower(a) == std::tolower(b);
			});
		}

		return false;
	}
}