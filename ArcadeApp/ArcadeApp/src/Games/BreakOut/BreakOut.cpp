#include "BreakOut.h"
#include <iostream>
#include "GameController.h"
#include "App.h"

void BreakOut::Init(GameController& gameController)
{
	gameController.CleaAll();
	ResetGame();

	ButtonAction serveAction;
	serveAction.key = GameController::ActionKey();
	serveAction.action = [this](uint32_t dt, InputState state)
	{
		if (mGameState == IN_SERVE)
		{
			if (GameController::IsPressed(state))
			{
				mGameState = IN_PLAY;

				if (mPaddle.IsMovingLeft())
				{
					mBall.SetVelocity(Vec2D(-INITAIL_BALL_SPEED, INITAIL_BALL_SPEED));
				}
				else
				{
					mBall.SetVelocity(Vec2D(INITAIL_BALL_SPEED, -INITAIL_BALL_SPEED));
				}
			}
		}
		else if (mGameState == IN_GAME_OVER)
		{
			if (GameController::IsPressed(state))
			{
				ResetGame();
			}
		}
	};

	gameController.AddInputAction(serveAction);

	ButtonAction leftKeyAction;
	leftKeyAction.key = GameController::LeftKey();
	leftKeyAction.action = [this](uint32_t dt, InputState state)
	{
		if (mGameState == IN_PLAY || mGameState == IN_SERVE)
		{
			if (GameController::IsPressed(state))
			{
				mPaddle.SetMovementDirection(PaddleDirection::LEFT);
			}
			else
			{
				mPaddle.UnsetMovementDirection(PaddleDirection::LEFT);
			}
		}
	};

	gameController.AddInputAction(leftKeyAction);

	ButtonAction rightKeyAction;
	rightKeyAction.key = GameController::RightKey();
	rightKeyAction.action = [this](uint32_t dt, InputState state)
	{
		if (mGameState == IN_PLAY || mGameState == IN_SERVE)
		{
			if (GameController::IsPressed(state))
			{
				mPaddle.SetMovementDirection(PaddleDirection::RIGHT);
			}
			else
			{
				mPaddle.UnsetMovementDirection(PaddleDirection::RIGHT);
			}
		}
	};

	gameController.AddInputAction(rightKeyAction);
}

void BreakOut::Update(uint32_t dt)
{
	if (mGameState == IN_SERVE)
	{
		mPaddle.Update(dt, mBall);
		SetToServeState();
	}
	else if (mGameState == IN_PLAY)
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
	mCurrentLevel = 2;

	AARectangle paddleRect = {
		// Top left
		Vec2D(App::Singletone().Width() / 2 - Paddle::PADDLE_WIDTH / 2, App::Singletone().Height() - 3 * Paddle::PADDLE_HEIGHT),
		Paddle::PADDLE_WIDTH, Paddle::PADDLE_HEIGHT
	};
	AARectangle levelBoundary = { Vec2D::Zero, App::Singletone().Width(), App::Singletone().Height() };

	mLevelBoundary = { levelBoundary };
	mPaddle.Init(paddleRect, levelBoundary);
	mBall.MoveTo(Vec2D(App::Singletone().Width() / 2, App::Singletone().Height() * 0.75f));
	
	SetToServeState();
}

void BreakOut::SetToServeState()
{
	mGameState = IN_SERVE;
	mBall.Stop();
	mBall.MoveTo(Vec2D(mPaddle.GetRectangle().GetCenterPoint().GetX(), mPaddle.GetRectangle().GetTopLeftPoint().GetY() - mBall.GetRadius() - 1));
}