#include "Paddle.h"
#include "Screen.h"
#include "Utils.h"
#include "BoundaryEdge.h"
#include "Ball.h"
#include <cassert>

void Paddle::Init(const AARectangle& rect, const AARectangle& boundary)
{
	Excluder::Init(rect);
	mBoundary = boundary;
}

void Paddle::Update(uint32_t dt, Ball& ball)
{
	if (GetRectangle().ContainsPoint(ball.GetPosition()))
	{
		Vec2D pointOnEdge;
		ball.MakeFlushWithEdge(GetEdge(BOTTOM_EDGE), pointOnEdge, true);
	}

	if (mDirection != 0)
	{
		Vec2D dir;
		if ((mDirection & PaddleDirection::LEFT) == PaddleDirection::LEFT &&
			(mDirection & PaddleDirection::RIGHT) == PaddleDirection::RIGHT)
		{
			dir = Vec2D::Zero;
		}
		else
		{
			dir = (mDirection == PaddleDirection::LEFT) ? LEFT_DIR : RIGHT_DIR;
		}

		Vec2D dx = dir * mVelocity * MillisecondsToSeconds(dt);

		MoveBy(dx);

		const AARectangle& rect = GetRectangle();

		if (GreaterThanOrEqual(mBoundary.GetTopLeftPoint().GetX(), rect.GetTopLeftPoint().GetX()))
		{
			MoveTo(Vec2D(mBoundary.GetTopLeftPoint().GetX(), rect.GetTopLeftPoint().GetY()));
		}
		else if (GreaterThanOrEqual(rect.GetBottomRightPoint().GetX(), mBoundary.GetBottomRightPoint().GetX()))
		{
			MoveTo(Vec2D(mBoundary.GetBottomRightPoint().GetX() - rect.GetWidth(), rect.GetTopLeftPoint().GetY()));
		}
	}
}

void Paddle::Draw(Screen& screen)
{
	screen.Draw(GetRectangle(), Color::Blue(), true, Color::Blue());
}

bool Paddle::Bounce(Ball& ball)
{
	BoundaryEdge edge;

	if (HasCollided(ball.GetBoundingRect(), edge))
	{
		Vec2D edgePoint;

		ball.MakeFlushWithEdge(edge, edgePoint, true);

		if (edge.edge == GetEdge(TOP_EDGE).edge)
		{
			float edgeLength = edge.edge.Length();
			assert(!Equals(edgeLength, 0));
			float tx = (edgePoint.GetX() - edge.edge.GetP0().GetX()) / edgeLength;

			if (((tx <= mCornerBounceAmount) && ball.GetVelocity().GetX() > 0) ||
				(tx >= (1.0f - mCornerBounceAmount) && ball.GetVelocity().GetX() < 0))
			{
				ball.SetVelocity(-ball.GetVelocity());
				return true;
			}
		}

		ball.SetVelocity(ball.GetVelocity().Reflect(edge.normal));
		return true;
	}

	return false;
}