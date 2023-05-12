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