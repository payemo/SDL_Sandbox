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
		case SDL_MOUSEMOTION:
		{
			if (mCurrentGameController)
			{
				MouseMovedAction mouseMoved = mCurrentGameController->GetMouseMovedAction();
				if (mouseMoved)
				{
					MousePosition pos;
					pos.xPos = event.motion.x;
					pos.yPos = event.motion.y;

					mouseMoved(pos);
				}
			}
			break;
		}
		case SDL_MOUSEBUTTONUP:
		case SDL_MOUSEBUTTONDOWN:
			if (mCurrentGameController)
			{
				MouseButton btn = static_cast<MouseButton>(event.button.button);
				MouseInputAction action = mCurrentGameController->GetMouseButtonAction(btn);

				MousePosition pos;
				pos.xPos = event.motion.x;
				pos.yPos = event.motion.y;

				action(static_cast<InputState>(event.button.state), pos);
			}
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