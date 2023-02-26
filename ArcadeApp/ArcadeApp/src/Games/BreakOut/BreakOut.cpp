#include "BreakOut.h"
#include <iostream>
#include "GameController.h"
#include "App.h"

void BreakOut::Init(GameController& gameController)
{
	gameController.CleaAll();
	ResetGame();

	ButtonAction leftKeyAction;
	leftKeyAction.key = GameController::LeftKey();
	leftKeyAction.action = [this](uint32_t dt, InputState state)
	{
		if (GameController::IsPressed(state))
		{
			mPaddle.SetMovementDirection(PaddleDirection::LEFT);
		}
		else
		{
			mPaddle.UnsetMovementDirection(PaddleDirection::LEFT);
		}
	};

	gameController.AddInputAction(leftKeyAction);

	ButtonAction rightKeyAction;
	rightKeyAction.key = GameController::RightKey();
	rightKeyAction.action = [this](uint32_t dt, InputState state)
	{
		if (GameController::IsPressed(state))
		{
			mPaddle.SetMovementDirection(PaddleDirection::RIGHT);
		}
		else
		{
			mPaddle.UnsetMovementDirection(PaddleDirection::RIGHT);
		}
	};

	gameController.AddInputAction(rightKeyAction);
}

void BreakOut::Update(uint32_t dt)
{
	mBall.Update(dt);
	mPaddle.Update(dt, mBall);

	BoundaryEdge edge;

	if (mPaddle.Bounce(mBall))
	{
		return;
	}

	if (mLevelBoundary.HasCollided(mBall, edge))
	{
		mBall.Bounce(edge);
		return;
	}

	GetCurrentLevel().Update(dt, mBall);
}

void BreakOut::Draw(Screen& screen)
{
	mBall.Draw(screen);
	mPaddle.Draw(screen);
	GetCurrentLevel().Draw(screen);
	screen.Draw(mLevelBoundary.GetRectangle(), Color::White());
}

const std::string& BreakOut::GetName() const
{
	static std::string name = "Break Out";
	return name;
}

void BreakOut::ResetGame()
{
	mLevels = BreakOutGameLevel::LoadLevelsFromFile(App::GetBasePath() + "BreakoutLevels.txt");
	mCurrentLevel = 0;

	AARectangle paddleRect = {
		// Top left
		Vec2D(App::Singletone().Width() / 2 - Paddle::PADDLE_WIDTH / 2, App::Singletone().Height() - 3 * Paddle::PADDLE_HEIGHT),
		Paddle::PADDLE_WIDTH, Paddle::PADDLE_HEIGHT
	};
	AARectangle levelBoundary = { Vec2D::Zero, App::Singletone().Width(), App::Singletone().Height() };

	mLevelBoundary = { levelBoundary };
	mPaddle.Init(paddleRect, levelBoundary);
	mBall.MoveTo(Vec2D(App::Singletone().Width() / 2, App::Singletone().Height() * 0.75f));
	mBall.SetVelocity(INITIAL_BALL_VELOCITY);
}