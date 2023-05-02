#pragma once

#include "Game.h"
#include "PacmanLevel.h"
#include "Pacman.h"
#include "SpriteSheet.h"
#include "InputAction.h"

class PacmanGame : public Game
{
public:
	void Init(GameController& gameController) override;
	void Update(uint32_t dt) override;
	void Draw(Screen& screen) override;
	const std::string& GetName() const override;

private:
	void ResetGame();
	void UpdatePacmanMovement();
	void HandleGameControllerState(uint32_t dt, InputState state, PacmanMovement direction);

	PacmanMovement mPressedDirection;
	SpriteSheet mPacmanSpriteSheet;
	Pacman mPacman;
	PacmanLevel mLevel;
};