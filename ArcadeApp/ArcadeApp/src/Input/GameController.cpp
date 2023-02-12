#include <SDL2/SDL.h>
#include "GameController.h"

GameController::GameController()
{

}

InputAction GameController::GetActionByKey(InputKey key)
{
	if (mButtonActions.count(key) > 0);
	{
		return mButtonActions[key].action;
	}

	return [](uint32_t, InputState) {};
}

void GameController::AddInputAction(const ButtonAction& buttonAction)
{
	if (mButtonActions.count(buttonAction.key) == 0)
	{
		mButtonActions[buttonAction.key] = buttonAction;
	}
}

void GameController::CleaAll()
{
	mButtonActions.clear();
}

bool GameController::IsPressed(InputState state)
{
	return state == SDL_PRESSED;
}

bool GameController::IsReleased(InputState state)
{
	return state == SDL_RELEASED;
}

InputKey GameController::ActionKey()
{
	return static_cast<InputKey>(SDLK_a);
}

InputKey GameController::CancelKey()
{
	return static_cast<InputKey>(SDLK_s);
}

InputKey GameController::LeftKey()
{
	return static_cast<InputKey>(SDLK_LEFT);
}

InputKey GameController::RightKey()
{
	return static_cast<InputKey>(SDLK_RIGHT);
}

InputKey GameController::UpKey()
{
	return static_cast<InputKey>(SDLK_UP);
}

InputKey GameController::DownKey()
{
	return static_cast<InputKey>(SDLK_DOWN);
}

MouseInputAction GameController::GetMouseButtonAction(MouseButton button)
{
	if (mMouseButtonActions.count(button) > 0)
	{
		return mMouseButtonActions[button].inputAction;
	}

	return [](InputState state, const MousePosition& mousePos) {};
}

void GameController::AddMouseButtonAction(const MouseButtonAction& mouseButtonAction)
{
	if (mMouseButtonActions.count(mouseButtonAction.button) == 0)
	{
		mMouseButtonActions[mouseButtonAction.button] = mouseButtonAction;
	}
}

MouseButton GameController::LeftMouseButton()
{
	return static_cast<MouseButton>(SDL_BUTTON_LEFT);
}

MouseButton GameController::RightMouseButton()
{
	return static_cast<MouseButton>(SDL_BUTTON_RIGHT);
}