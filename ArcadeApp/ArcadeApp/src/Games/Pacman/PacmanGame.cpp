#include "PacmanGame.h"
#include "App.h"
#include "PacmanGameUtils.h"

void PacmanGame::Init(GameController& gameController)
{
	mPacmanSpriteSheet.Load("PacmanSprites");

	mLevel.Init(App::Singletone().GetBasePath() + "src/Assets/Pacman_level.txt");

	mPacman.Init(mPacmanSpriteSheet, App::Singletone().GetBasePath() + "src/Assets/Pacman_animations.txt", Vec2D::Zero, PACMAN_MOVEMENT_SPEED, false);

	ResetGame();

	ButtonAction leftAction;
	leftAction.key = GameController::LeftKey();
	leftAction.action = [this](uint32_t dt, InputState state) {
		HandleGameControllerState(dt, state, PACMAN_MOVEMENT_LEFT);
	};

	gameController.AddInputAction(leftAction);

	ButtonAction rightAction;
	rightAction.key = GameController::RightKey();
	rightAction.action = [this](uint32_t dt, InputState state) {
		HandleGameControllerState(dt, state, PACMAN_MOVEMENT_RIGHT);
	};

	gameController.AddInputAction(rightAction);

	ButtonAction upAction;
	upAction.key = GameController::UpKey();
	upAction.action = [this](uint32_t dt, InputState state) {
		HandleGameControllerState(dt, state, PACMAN_MOVEMENT_UP);
	};

	gameController.AddInputAction(upAction);

	ButtonAction downAction;
	downAction.key = GameController::DownKey();
	downAction.action = [this](uint32_t dt, InputState state) {
		HandleGameControllerState(dt, state, PACMAN_MOVEMENT_DOWN);
	};

	gameController.AddInputAction(downAction);
}

void PacmanGame::Update(uint32_t dt)
{
	mLevel.Update(dt);
	UpdatePacmanMovement();
	mPacman.Update(dt);
}

void PacmanGame::Draw(Screen& screen)
{
	mLevel.Draw(screen);
	mPacman.Draw(screen);
}

const std::string& PacmanGame::GetName() const
{
	static std::string name = "Pacman";
	return name;
}

void PacmanGame::ResetGame()
{
	mPressedDirection = PACMAN_MOVEMENT_NONE;
	mPacman.ResetScore();
}

void PacmanGame::UpdatePacmanMovement()
{
	if (mPressedDirection != PACMAN_MOVEMENT_NONE)
	{
		mPacman.SetMovementDirection(mPressedDirection);
	}
}

void PacmanGame::HandleGameControllerState(uint32_t dt, InputState state, PacmanMovement direction)
{
	if (GameController::IsPressed(state))
	{
		mPressedDirection = direction;
	}
	else if(GameController::IsReleased(state) && mPressedDirection == direction)
	{
		mPressedDirection = PACMAN_MOVEMENT_NONE;
	}
}