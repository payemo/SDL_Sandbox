#include <iostream>
#include "Vec2D.h"
//#include "SDL2/SDL.h"

const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 640;

int main(int argc, char* args[])
{
	Vec2D v1(2, 5);
	Vec2D v2(4, 3);

	std::cout << "Magnitude of v1: " << v1.Mag() << std::endl;
	std::cout << "Magnitude of v2: " << v2.Mag() << std::endl;
	std::cout << "Distance between vectors is: " << v1.Distance(v2) << std::endl;
	return 1;
}

/*
int main()
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
} */