#pragma once

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"

class Game
{
public:

	Game() {}
	~Game();

	bool Init(const char* title, int xPos, int yPos, int width, int height, int flags);

	void Render();
	void Update();
	void HandleEvents();
	void Clean();

	bool IsRunning() { return is_running; }

private:
	SDL_Window* window{ nullptr };
	SDL_Renderer* renderer{ nullptr };

	int currentFrame{0};

	bool is_running;

};