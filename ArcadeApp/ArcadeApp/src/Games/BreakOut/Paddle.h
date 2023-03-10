#pragma once

#include "Excluder.h"
#include <stdint.h>

class Screen;
class Ball;

enum PaddleDirection
{
	LEFT = 1 << 0,
	RIGHT = 1 << 1
};

class Paddle : public Excluder
{
public:
	static const uint32_t PADDLE_WIDTH = 50;
	static const uint32_t PADDLE_HEIGHT = 10;

	void Init(const AARectangle& rect, const AARectangle& boundary);
	void Update(uint32_t dt, Ball& ball);
	void Draw(Screen& screen);

	bool Bounce(Ball& ball);

	inline bool IsMovingLeft() const { return mDirection == PaddleDirection::LEFT; }
	inline bool IsMovingRight() const { return mDirection == PaddleDirection::RIGHT; }

	inline void SetMovementDirection(PaddleDirection direction) { mDirection |= direction; };
	inline void UnsetMovementDirection(PaddleDirection direction) { mDirection &= ~direction; };
	inline void StopMovement() { mDirection = 0; }

private:
	uint32_t mDirection{0};
	AARectangle mBoundary;

	const float mVelocity = 100.f; // pixels per second
	const float mCornerBounceAmount = 0.2f; // percentage of a corner of paddle
};