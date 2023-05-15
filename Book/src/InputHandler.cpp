#include "InputHandler.h"
#include "Game.h"
#include <iostream>

InputHandler* InputHandler::m_instance = nullptr;

InputHandler::InputHandler()
{
}

void InputHandler::InitializedJoysticks()
{
    if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0) {
        SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    }

    if (SDL_NumJoysticks() > 0) {
        for (int i = 0; i < SDL_NumJoysticks(); ++i) {
            SDL_Joystick* joystick = SDL_JoystickOpen(i);

            if (SDL_JoystickOpen(i)) {
                m_joysticks.push_back(joystick);
                m_joystickValues.push_back(std::make_pair(
                    new Vector2D(0, 0), new Vector2D(0, 0)
                ));
            }
            else {
                std::cout << SDL_GetError() << std::endl;
            }
        }

        SDL_JoystickEventState(SDL_ENABLE);
        m_joystickIsInitialized = true;

        std::cout << "Initialized " << m_joysticks.size() << " joystick(s)";
    }
}

void InputHandler::Update()
{
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            TheGame::Instance()->Quit();
        }

        if (event.type == SDL_JOYAXISMOTION) {
            int whichOne = event.jaxis.which;

            // left stick move left or right
            if (event.jaxis.axis == 0) {
                if (event.jaxis.value > m_joystickDeadZone) {
                    m_joystickValues[whichOne].first->SetX(1);
                }
                else if (event.jaxis.value < -m_joystickDeadZone) {
                    m_joystickValues[whichOne].first->SetX(-1);
                }
                else {
                    m_joystickValues[whichOne].first->SetX(0);
                }
            }

            // left stick move up/down
            if (event.jaxis.axis == 1) {
                if (event.jaxis.value > m_joystickDeadZone) {
                    m_joystickValues[whichOne].first->SetY(1);
                }
                else if (event.jaxis.value < -m_joystickDeadZone) {
                    m_joystickValues[whichOne].first->SetY(-1);
                }
                else {
                    m_joystickValues[whichOne].first->SetY(0);
                }
            }

            // right stick move left/right
            if (event.jaxis.axis == 3) {
                if (event.jaxis.value > m_joystickDeadZone) {
                    m_joystickValues[whichOne].second->SetX(1);
                }
                else if (event.jaxis.value < -m_joystickDeadZone) {
                    m_joystickValues[whichOne].second->SetX(-1);
                }
                else {
                    m_joystickValues[whichOne].second->SetX(0);
                }
            }

            // right stick move up/down
            if (event.jaxis.axis == 4) {
                if (event.jaxis.value > m_joystickDeadZone) {
                    m_joystickValues[whichOne].second->SetY(1);
                }
                else if (event.jaxis.value < -m_joystickDeadZone) {
                    m_joystickValues[whichOne].second->SetY(-1);
                }
                else {
                    m_joystickValues[whichOne].second->SetY(0);
                }
            }
        }
    }
}

void InputHandler::Clean()
{
    if (m_joystickIsInitialized) {
        for (int i = 0; i < m_joysticks.size(); ++i) {
            SDL_JoystickClose(m_joysticks[i]);
        }
    }
}

int InputHandler::XValue(int joyId, int stick)
{
    if (m_joystickValues.size() > 0) {
        if (stick == 1) {
            return m_joystickValues[joyId].first->GetX();
        }
        else if(stick == 2) {
            return m_joystickValues[joyId].second->GetX();
        }
    }
    return 0;
}

int InputHandler::YValue(int joyId, int stick)
{
    if (m_joystickValues.size() > 0) {
        if (stick == 1) {
            return m_joystickValues[joyId].first->GetY();
        }
        else if (stick == 2) {
            return m_joystickValues[joyId].second->GetY();
        }
    }
    return 0;
}