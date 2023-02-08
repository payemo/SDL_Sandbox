#pragma once
#include "Shape.h"

class Circle : public Shape
{
public:
	Circle();
	Circle(const Vec2D& center, float radius);

	inline virtual Vec2D GetCenterPoint() const override { return mPoints[0]; }
	inline float GetRadius() const { return mRadius; }
	inline void SetRadius(float radius) { mRadius = radius; }
	inline void MoveTo(const Vec2D& pos) { mPoints[0] = pos; }

	bool Intersects(const Circle& otherCircle) const;
	bool ContainsPoint(const Vec2D& point) const;
private:
	float mRadius;
};