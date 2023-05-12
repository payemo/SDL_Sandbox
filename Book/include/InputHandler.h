#pragma once

#include <vector>
#include "SDL.h"

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

    inline bool JoystickInitialized() { return m_joystickIsInitialized; }

private:
    InputHandler();
    ~InputHandler() {}

    std::vector<SDL_Joystick*> m_joysticks;
    bool m_joystickIsInitialized{ false };

private:
    static InputHandler* m_instance;
};

typedef InputHandler TheInputHandler;