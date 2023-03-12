#include "BreakOut.h"
#include <iostream>
#include "GameController.h"
#include "App.h"
#include "Circle.h"

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

	ButtonAction backAction;
	backAction.key = GameController::CancelKey();
	backAction.action = [this](uint32_t dt, InputState state)
	{
		if (mGameState == IN_SERVE || mGameState == IN_GAME_OVER)
		{
			if (GameController::IsPressed(state))
			{
				App::Singletone().PopScene();
			}
		}
	};

	gameController.AddInputAction(backAction);
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

		if (IsBallPassedCutOffY())
		{
			ReduceLifeByOne();

			if (!IsGameOver())
			{
				SetToServeState();
			}
			else
			{
				mGameState = IN_GAME_OVER;
			}
		}
		else if (GetCurrentLevel().IsLevelComplete())
		{
			mCurrentLevel = (mCurrentLevel + 1) % mLevels.size();
			ResetGame(mCurrentLevel);
		}
	}
}

void BreakOut::Draw(Screen& screen)
{
	mBall.Draw(screen);
	mPaddle.Draw(screen);
	GetCurrentLevel().Draw(screen);
	screen.Draw(mLevelBoundary.GetRectangle(), Color::White());

	Circle lifeCircle = { Vec2D(7, App::Singletone().Height() - 10), 5 };

	for (int i = 0; i < mLives; ++i)
	{
		screen.Draw(lifeCircle, Color::Red(), true, Color::Red());
		lifeCircle.MoveBy(Vec2D(17, 0));
	}
}

const std::string& BreakOut::GetName() const
{
	static std::string name = "Break Out";
	return name;
}

void BreakOut::ResetGame(size_t toLevel)
{
	mLevels = BreakOutGameLevel::LoadLevelsFromFile(App::GetBasePath() + "src/Assets/BreakoutLevels.txt");
	mYCutOff = App::Singletone().Height() - 2 * Paddle::PADDLE_HEIGHT;
	mLives = NUM_LIVES;
	mCurrentLevel = toLevel;

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

bool BreakOut::IsBallPassedCutOffY() const
{
	return mBall.GetPosition().GetY() > mYCutOff;
}

void BreakOut::ReduceLifeByOne()
{
	if (mLives >= 0)
	{
		--mLives;
	}
}