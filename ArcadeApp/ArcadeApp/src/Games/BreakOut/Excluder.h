#pragma once

#include "AARectangle.h"
#include "BoundaryEdge.h"

class Excluder
{
public:
	virtual ~Excluder() {};

	void Init(const AARectangle& rect, bool reverseNormals = false);
	bool HasCollided(const AARectangle& rect, BoundaryEdge& edge) const;
	Vec2D GetCollisionOffset(const AARectangle& rect) const;
	inline const AARectangle& GetRectangle() const { return mRect; }
	void MoveBy(const Vec2D& delta);
	void MoveTo(const Vec2D& point);
	const BoundaryEdge& GetEdge(EdgeType edge) const;

private:
	void SetupEdges();

	AARectangle mRect;
	BoundaryEdge mEdges[4];
	bool mReverseNormals;
};