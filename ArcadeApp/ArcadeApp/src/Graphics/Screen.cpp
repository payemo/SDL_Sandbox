#include "Screen.h"
#include "Vec2D.h"
#include "Line2D.h"
#include <SDL2/SDL.h>
#include <cassert>
#include <cmath>

Screen::Screen() : mWidth(0), mHeight(0), mWindow(nullptr), mWindowSurface(nullptr)
{

}

Screen::~Screen()
{
	if (mWindow)
	{
		SDL_DestroyWindow(mWindow);
		mWindow = nullptr;
		SDL_Quit();
	}
}

SDL_Window* Screen::Init(uint32_t w, uint32_t h, uint32_t mag)
{
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		std::cerr << "SDL_Init failed!" << std::endl;
		return nullptr;
	}

	mWidth = w;
	mHeight = h;

	mWindow = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mWidth * mag, mHeight * mag, 0);

	if (mWindow)
	{
		mWindowSurface = SDL_GetWindowSurface(mWindow);
		SDL_PixelFormat* pixFormat = mWindowSurface->format;
		Color::InitColorFormat(pixFormat);

		mClearColor = Color::Black();

		mBackBuffer.Init(pixFormat->format, mWidth, mHeight);
		mBackBuffer.Clear(mClearColor);
	}

	return mWindow;
}

void Screen::SwapScreens()
{
	assert(mWindow);
	if (mWindow)
	{
		// clear the front buffer
		ClearScreen();

		SDL_BlitScaled(mBackBuffer.GetSurface(), nullptr, mWindowSurface, nullptr);

		SDL_UpdateWindowSurface(mWindow);

		mBackBuffer.Clear(mClearColor);
	}
}

void Screen::Draw(int x, int y, const Color& color)
{
	assert(mWindow);
	if (mWindow)
	{
		mBackBuffer.SetPixel(color, x, y);
	}
}

void Screen::Draw(const Vec2D& point, const Color& color)
{
	assert(mWindow);
	if (mWindow)
	{
		mBackBuffer.SetPixel(color, point.GetX(), point.GetY());
	}
}

void Screen::Draw(const Line2D& line, const Color& color)
{
	assert(mWindow);
	if (mWindow)
	{
		int dx, dy;

		int x0 = roundf(line.GetP0().GetX());
		int y0 = roundf(line.GetP0().GetY());
		int x1 = roundf(line.GetP1().GetX());
		int y1 = roundf(line.GetP1().GetY());

		dx = x1 - x0;
		dy = y1 - y0;

		signed const char ix((dx > 0) - (dx < 0));
		signed const char iy((dy > 0) - (dy < 0));

		dx = abs(dx) * 2;
		dy = abs(dy) * 2;

		Draw(x0, y0, color);

		if (dx >= dy)
		{
			int d = dy - dx / 2;

			while (x0 != x1)
			{
				if (d >= 0)
				{
					d -= dx;
					y0 += iy;
				}
				d += dy;
				x0 += ix;

				Draw(x0, y0, color);
			}
		}
		else
		{
			int d = dx - dy / 2;

			while (y0 != y1)
			{
				if (d >= 0)
				{
					d -= dy;
					x0 += ix;
				}
				d += dx;
				y0 += iy;

				Draw(x0, y0, color);
			}
		}
	}
}

void Screen::ClearScreen()
{
	assert(mWindow);
	if (mWindow)
	{
		SDL_FillRect(mWindowSurface, nullptr, mClearColor.GetPixelColor());
	}
}