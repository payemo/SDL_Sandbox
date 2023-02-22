#include "Triangle.h"
#include <cmath>
#include "Utils.h"

Triangle::Triangle() : Triangle(Vec2D::Zero, Vec2D::Zero, Vec2D::Zero)
{
}

Triangle::Triangle(const Vec2D& p0, const Vec2D& p1, const Vec2D& p2)
{
	mPoints.push_back(p0);
	mPoints.push_back(p1);
	mPoints.push_back(p2);
}

Vec2D Triangle::GetCenterPoint() const
{
	return Vec2D(
		(mPoints[0].GetX() + mPoints[1].GetX() + mPoints[2].GetX()) / 3.f,
		(mPoints[0].GetY() + mPoints[1].GetY() + mPoints[2].GetY()) / 3.f);
}

float Triangle::Area() const
{
	return Area(GetP0(), GetP1(), GetP2());
}

bool Triangle::ContainsPoint(const Vec2D& p) const
{
	float thisArea = Area();

	float a1 = Area(p, GetP1(), GetP2());
	float a2 = Area(GetP0(), p, GetP2());
	float a3 = Area(GetP0(), GetP1(), p);

	return Equals(thisArea, a1 + a2 + a3);
}

float Triangle::Area(const Vec2D& p0, const Vec2D& p1, const  Vec2D& p2) const
{
	return fabs((p0.GetX() * (p1.GetY() - p2.GetY()) + p1.GetX() * (p2.GetY() - p1.GetY()) + p2.GetX() * (p0.GetY() - p1.GetY())) / 2.f);
}