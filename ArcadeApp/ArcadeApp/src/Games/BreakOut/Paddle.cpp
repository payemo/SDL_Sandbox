#include "Paddle.h"
#include "Screen.h"
#include "Utils.h"
#include "BoundaryEdge.h"

void Paddle::Init(const AARectangle& rect, const AARectangle& boundary)
{
	Excluder::Init(rect);
	mBoundary = boundary;
}

void Paddle::Update(uint32_t dt)
{
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