#pragma once

#include <vector>
#include <utility>
#include "SDL.h"
#include <Vector2D.h>

enum MouseButtons
{
    LEFT = 0,
    MIDDLE = 1, 
    RIGHT = 2
};

class InputHandler
{
public:
    static InputHandler* Instance()
    {
        if (!m_instance) {
            m_instance = new InputHandler;
        }

        return m_instance;
    }

    void Update();
    void Clean();

    void InitializedJoysticks();

    int XValue(int joyId, int stick);
    int YValue(int joyId, int stick);

    inline bool JoystickInitialized() { return m_joystickIsInitialized; }

    inline bool GetMouseButtonState(int buttonNumber) { return m_mouseButtonStates[buttonNumber]; }
    inline const Vector2D& GetMousePosition() { return *m_mousePosition; }

    bool isKeyDown(SDL_Scancode key) {
        if (m_keyStates != nullptr) {
            return m_keyStates[key] == 1;
        }
        return false;
    }

private:
    InputHandler();
    ~InputHandler() {}

    std::vector<bool> m_mouseButtonStates;
    Vector2D* m_mousePosition;

    const Uint8* m_keyStates;

    std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;
    std::vector<SDL_Joystick*> m_joysticks;
    bool m_joystickIsInitialized{ false };

private:
    static InputHandler* m_instance;

    static const int m_joystickDeadZone = 10000;
};

typedef InputHandler TheInputHandler;