#include <iostream>
#include "SDL2/SDL.h"

#include "Color.h"
#include "Screen.h"

const int SCREEN_WIDTH = 224;
const int SCREEN_HEIGHT = 288;
const int MAGNIFICATION = 3;

int main(int argc, char* argv[])
{
	Screen screen;
	screen.Init(SCREEN_WIDTH, SCREEN_HEIGHT, MAGNIFICATION);
	screen.Draw(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, Color::Yellow());
	screen.SwapScreens();

	SDL_Event event;
	bool running = true;

	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.key.keysym.sym == SDLK_ESCAPE || event.type == SDL_QUIT)
			{
				running = false;
				break;
			}
		}
	}

	

	return 0;
} 