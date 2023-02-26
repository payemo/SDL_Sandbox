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
	const int NUM_LIVES = 3;

	void ResetGame(size_t toLevel = 0);
	BreakOutGameLevel& GetCurrentLevel() { return mLevels[mCurrentLevel]; }
	void SetToServeState();

	bool IsBallPassedCutOffY() const; // ball passed under the paddle
	void ReduceLifeByOne();
	inline bool IsGameOver() const { return mLives < 0; }

	const float INITAIL_BALL_SPEED = 100;
	const Vec2D INITIAL_BALL_VELOCITY{ Vec2D(100, -100) };

	Paddle mPaddle;
	Ball mBall;
	LevelBoundary mLevelBoundary;
	std::vector<BreakOutGameLevel> mLevels;
	size_t mCurrentLevel;
	BreakOutGameState mGameState;
	int mLives;
	float mYCutOff;
};