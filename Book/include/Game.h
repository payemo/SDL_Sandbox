#pragma once

#include <iostream>
#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "GameObject.h"

class Game
{
public:
    static Game* Instance();

public:
    //~Game();

    bool Init(const char* title, int xPos, int yPos, int width, int height, int flags);

    void HandleEvents();
    void Update();
    void Render();
    void Clean();

    bool IsRunning() { return is_running; }

    inline SDL_Renderer& GetRenderer() const { return *renderer; }

private:
    Game() {}

    static Game* m_instance;

    SDL_Window* window{ nullptr };
    SDL_Renderer* renderer{ nullptr };

    std::vector<GameObject*> m_gameObjects;

    int currentFrame{ 0 };

    bool is_running{ false };

};

typedef Game TheGame;