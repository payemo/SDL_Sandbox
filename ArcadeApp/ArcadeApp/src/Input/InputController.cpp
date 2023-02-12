#include "InputController.h"
#include <SDL2/SDL.h>

void InputController::Init(InputAction quitAction)
{
	mQuit = quitAction;
}

void InputController::Update(uint32_t dt)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mQuit(dt, SDL_PRESSED);
			break;
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			if (mCurrentGameController)
			{
				InputAction action = mCurrentGameController->GetActionByKey(event.key.keysym.sym);
				action(dt, static_cast<InputState>(event.key.state));
			}
			break;
		}
	}
}

void InputController::SetGameController(GameController* controller)
{
	mCurrentGameController = controller;
}