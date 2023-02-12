#pragma once

#include "InputAction.h"
#include "GameController.h"

class InputController
{
public:
	void Init(InputAction action);
	void Update(uint32_t dt);

	void SetGameController(GameController* controller);
private:
	InputAction mQuit{ nullptr };
	GameController* mCurrentGameController{ nullptr };
};