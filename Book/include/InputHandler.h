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
    inline bool GettButtonState(int joy, int buttonNumber) const { return m_buttonStates[joy][buttonNumber]; }

    bool isKeyPressed(SDL_Scancode key);

    // handle keybord
    void onKeyPressed(SDL_Event& event);

    // handle mouse events
    void onMouseMove(SDL_Event& event);
    void onMouseButtonDown(SDL_Event& event);
    void onMouseButtonUp(SDL_Event& event);

    // handle joystick events
    void onJoystickAxisMove(SDL_Event& event);
    void onJoystickButtonDown(SDL_Event& event);
    void onJoystickButtonUp(SDL_Event& event);

private:
    InputHandler();
    ~InputHandler() {}

    std::vector<bool> m_mouseButtonStates;
    Vector2D* m_mousePosition;

    const Uint8* m_keyStates;

    // joystick specific
    std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;
    std::vector<SDL_Joystick*> m_joysticks;
    std::vector<std::vector<bool>> m_buttonStates;
    bool m_joystickIsInitialized{ false };

private:
    static InputHandler* m_instance;

    static const int m_joystickDeadZone = 10000;
};

typedef InputHandler TheInputHandler;