#pragma once

#include "Excluder.h"

class AARectangle;
class Ball;

class LevelBoundary
{
public:
	LevelBoundary() {}
	LevelBoundary(const AARectangle& boundary);
	bool HasCollided(const Ball& ball, BoundaryEdge& edge);
	inline const AARectangle& GetRectangle() const { return mIncluder.GetRectangle(); }

private:
	bool HasCollidedWithEdge(const Ball& ball, const BoundaryEdge& edge) const;

	Excluder mIncluder;
};