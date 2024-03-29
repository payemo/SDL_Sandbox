#pragma once

#include <iostream>
#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "GameObject.h"
#include "GameStateMachine.h"

class Game
{
public:
    static Game* Instance();

public:
    ~Game();

    bool Init(const char* title, int xPos, int yPos, int width, int height, int flags);

    void HandleEvents();
    void Update();
    void Render();
    void Clean();

    inline bool IsRunning() { return is_running; }
    inline void Quit() { is_running = false; }

    inline SDL_Renderer& GetRenderer() const { return *renderer; }
    inline GameStateMachine& GetStateMachine() const { return *m_gameStateMachine; }

    inline int GetWidth() const { return m_width; }
    inline int GetHeight() const { return m_height; }

private:
    static Game* m_instance;

private:
    Game() {}

    SDL_Window* window{ nullptr };
    SDL_Renderer* renderer{ nullptr };

    GameStateMachine* m_gameStateMachine{ nullptr };

    bool is_running{ false };


    int m_width;
    int m_height;

};

typedef Game TheGame;