#include "Excluder.h"
#include "Utils.h"
#include <cmath>

void Excluder::Init(const AARectangle& rect, bool reverseNormals)
{
	mRect = rect;
	mReverseNormals = reverseNormals;
}

bool Excluder::HasCollided(const AARectangle& rect, BoundaryEdge& edge) const
{
	if (mRect.Intersects(rect))
	{
		float yMin = mRect.GetTopLeftPoint().GetY() >= rect.GetTopLeftPoint().GetY() ?
			mRect.GetTopLeftPoint().GetY() : rect.GetTopLeftPoint().GetY();
		float yMax = mRect.GetBottomRightPoint().GetY() <= rect.GetBottomRightPoint().GetY() ?
			mRect.GetBottomRightPoint().GetY() : rect.GetBottomRightPoint().GetY();

		float ySize = yMax - yMin;

		float xMin = mRect.GetTopLeftPoint().GetX() >= rect.GetTopLeftPoint().GetX() ?
			mRect.GetTopLeftPoint().GetX() : rect.GetTopLeftPoint().GetX();
		float xMax = mRect.GetBottomRightPoint().GetX() <= rect.GetBottomRightPoint().GetX() ?
			mRect.GetBottomRightPoint().GetX() : rect.GetBottomRightPoint().GetX();

		float xSize = xMax - xMin;

		if (xSize > ySize)
		{
			if (rect.GetCenterPoint().GetY() > mRect.GetCenterPoint().GetY())
			{
				edge = mEdges[BOTTOM_EDGE];
			}
			else
			{
				edge = mEdges[TOP_EDGE];
			}
		}
		else
		{
			if (rect.GetCenterPoint().GetX() > mRect.GetCenterPoint().GetX())
			{
				edge = mEdges[LEFT_EDGE];
			}
			else
			{
				edge = mEdges[RIGHT_EDGE];
			}
		}

		return true;
	}

	return false;
}

Vec2D Excluder::GetCollisionOffset(const AARectangle& rect) const
{
	BoundaryEdge edge;
	Vec2D offset = Vec2D::Zero;

	if (HasCollided(rect, edge))
	{
		if (!Equals(edge.normal.GetY(), 0))
		{
			float yMin = mRect.GetTopLeftPoint().GetY() >= rect.GetTopLeftPoint().GetY() ?
				mRect.GetTopLeftPoint().GetY() : rect.GetTopLeftPoint().GetY();
			float yMax = mRect.GetBottomRightPoint().GetY() <= rect.GetBottomRightPoint().GetY() ?
				mRect.GetBottomRightPoint().GetY() : rect.GetBottomRightPoint().GetY();

			float ySize = yMax - yMin;

			offset = (ySize * 1) * edge.normal;
		}
		else
		{
			float xMin = mRect.GetTopLeftPoint().GetX() >= rect.GetTopLeftPoint().GetX() ?
				mRect.GetTopLeftPoint().GetX() : rect.GetTopLeftPoint().GetX();
			float xMax = mRect.GetBottomRightPoint().GetX() <= rect.GetBottomRightPoint().GetX() ?
				mRect.GetBottomRightPoint().GetX() : rect.GetBottomRightPoint().GetX();

			float xSize = xMax - xMin;

			offset = (xSize + 1) * edge.normal;
		}
	}
	return offset;
}

void Excluder::MoveBy(const Vec2D& delta)
{
	mRect.MoveBy(delta);
	SetupEdges();
}

void Excluder::MoveTo(const Vec2D& point)
{
	mRect.MoveTo(point);
	SetupEdges();
}

const BoundaryEdge& Excluder::GetEdge(EdgeType edge) const
{
	return mEdges[edge];
}

// private
void Excluder::SetupEdges()
{
	mEdges[TOP_EDGE].edge = {
		mRect.GetTopLeftPoint().GetX(), mRect.GetTopLeftPoint().GetY(),
		mRect.GetBottomRightPoint().GetX(), mRect.GetTopLeftPoint().GetY()
	};
	mEdges[TOP_EDGE].normal = UP_DIR;

	mEdges[LEFT_EDGE].edge = {
		mRect.GetTopLeftPoint().GetX(), mRect.GetTopLeftPoint().GetY(),
		mRect.GetTopLeftPoint().GetX(), mRect.GetBottomRightPoint().GetY()
	};
	mEdges[LEFT_EDGE].normal = LEFT_DIR;

	mEdges[BOTTOM_EDGE].edge = {
		mRect.GetTopLeftPoint().GetX(), mRect.GetBottomRightPoint().GetY(),
		mRect.GetBottomRightPoint().GetX(), mRect.GetBottomRightPoint().GetY()
	};
	mEdges[BOTTOM_EDGE].normal = DOWN_DIR;

	mEdges[RIGHT_EDGE].edge = {
		mRect.GetBottomRightPoint().GetX(), mRect.GetTopLeftPoint().GetY(),
		mRect.GetBottomRightPoint().GetX(), mRect.GetBottomRightPoint().GetY()
	};
	mEdges[RIGHT_EDGE].normal = RIGHT_DIR;

	if (mReverseNormals)
	{
		for (auto& edge : mEdges)
		{
			edge.normal = -edge.normal;
		}
	}
}