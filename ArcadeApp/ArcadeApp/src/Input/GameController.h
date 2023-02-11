#pragma once

#include "InputAction.h"
#include <vector>
#include <map>

class GameController
{
	using ActionLookup = std::map<InputKey, ButtonAction>;
public:
	GameController();
	InputAction GetActionByKey(InputKey key);
	void AddInputAction(const ButtonAction& buttonAction);
	void CleaAll();

	static bool IsPressed(InputState state);
	static bool IsReleased(InputState state);
	static InputKey ActionKey();
	static InputKey CancelKey();
	static InputKey LeftKey();
	static InputKey RightKey();
	static InputKey UpKey();
	static InputKey DownKey();

private:
	//std::vector<ButtonAction> mButtonActions;
	ActionLookup mButtonActions;
};