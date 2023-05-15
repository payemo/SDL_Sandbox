#pragma once

#include <vector>
#include <utility>
#include "SDL.h"
#include <Vector2D.h>

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

private:
    InputHandler();
    ~InputHandler() {}

    std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;
    std::vector<SDL_Joystick*> m_joysticks;
    bool m_joystickIsInitialized{ false };

private:
    static InputHandler* m_instance;

    static const int m_joystickDeadZone = 10000;
};

typedef InputHandler TheInputHandler;