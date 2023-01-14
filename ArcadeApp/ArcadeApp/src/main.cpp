#include <iostream>
#include "SDL2/SDL.h"

#include "Color.h"
#include "ScreenBuffer.h"

const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 640;

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		std::cerr << "SDL_Init failed!" << std::endl;
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

	if (window == nullptr)
	{
		std::cerr << "Could not create window." << std::endl;
		return 1;
	}

	SDL_Surface* windowSurface = SDL_GetWindowSurface(window);
	SDL_PixelFormat* pixFormat = windowSurface->format;

	Color::InitColorFormat(pixFormat);

	ScreenBuffer sb;
	sb.Init(pixFormat->format, windowSurface->w, windowSurface->h);

	sb.SetPixel(Color::Red(), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	SDL_BlitSurface(sb.GetSurface(), nullptr, windowSurface, nullptr);

	SDL_UpdateWindowSurface(window);

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

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
} 