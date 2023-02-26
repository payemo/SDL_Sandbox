#pragma once

#include "Game.h"
#include "Paddle.h"
#include "Ball.h"
#include "LevelBoundary.h"
#include "BreakOutGameLevel.h"
#include <vector>

enum BreakOutGameState
{
	IN_PLAY = 0,
	IN_SERVE,
	IN_GAME_OVER
};

class BreakOut : public Game
{
public:
	virtual void Init(GameController& gameController) override;
	virtual void Update(uint32_t dt) override;
	virtual void Draw(Screen& screen) override;
	virtual const std::string& GetName() const override;

private:
	void ResetGame();
	BreakOutGameLevel& GetCurrentLevel() { return mLevels[mCurrentLevel]; }
	void SetToServeState();

	const float INITAIL_BALL_SPEED = 100;
	const Vec2D INITIAL_BALL_VELOCITY{ Vec2D(100, -100) };

	Paddle mPaddle;
	Ball mBall;
	LevelBoundary mLevelBoundary;
	std::vector<BreakOutGameLevel> mLevels;
	size_t mCurrentLevel;
	BreakOutGameState mGameState;
};