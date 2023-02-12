#pragma once

#include "InputAction.h"
#include <vector>
#include <map>

class GameController
{
	using InputActionLookup = std::map<InputKey, ButtonAction>;
	using MouseActionLookup = std::map<MouseButton, MouseButtonAction>;
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

	inline const MouseMovedAction& GetMouseMovedAction() { return mMouseMovedAction; }
	inline void SetMouseMovedAction(const MouseMovedAction& mouseMovedAction) { mMouseMovedAction = mouseMovedAction; }

	MouseInputAction GetMouseButtonAction(MouseButton button);
	void AddMouseButtonAction(const MouseButtonAction& mouseButtonAction);

	static MouseButton LeftMouseButton();
	static MouseButton RightMouseButton();

private:
	InputActionLookup mButtonActions;
	MouseActionLookup mMouseButtonActions;
	MouseMovedAction mMouseMovedAction{ nullptr };
};