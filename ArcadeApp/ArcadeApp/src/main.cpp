#include <iostream>
#include "SDL2/SDL.h"

#include "Color.h"
#include "Screen.h"
#include "Line2D.h"
#include "Triangle.h"
#include "AARectangle.h"
#include "Circle.h"

const int SCREEN_WIDTH = 224;
const int SCREEN_HEIGHT = 288;
const int MAGNIFICATION = 3;

int main(int argc, char* argv[])
{
	Screen screen;
	screen.Init(SCREEN_WIDTH, SCREEN_HEIGHT, MAGNIFICATION);

	Line2D line = { Vec2D(0, 0), Vec2D(SCREEN_WIDTH, SCREEN_HEIGHT) };
	Triangle triangle = { Vec2D(60, 10), Vec2D(10, 110), Vec2D(110, 110) };
	AARectangle rect = { Vec2D(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 25), 50, 50 };
	Circle circle = { Vec2D(SCREEN_WIDTH / 2 + 50, SCREEN_HEIGHT / 2 + 50), 50 };

	//creen.Draw(circle, Color::Pink(), true, Color::Pink());
	screen.Draw(triangle, Color::Red(), true, Color::Red());
	screen.Draw(rect, Color::Blue(), true, Color::Blue());
	screen.Draw(circle, Color(0, 255, 0, 150), true, Color(0, 255, 0, 150));
	//screen.Draw(line, Color::White());
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