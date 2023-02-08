#include "Shape.h"

void Shape::MoveBy(const Vec2D& deltaOffset)
{
	for (auto& point : mPoints)
	{
		point += deltaOffset;
	}
}