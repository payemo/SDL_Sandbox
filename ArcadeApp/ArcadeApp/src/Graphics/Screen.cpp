#include "Screen.h"
#include "Vec2D.h"
#include <SDL2/SDL.h>
#include <cassert>

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

void Screen::ClearScreen()
{
	assert(mWindow);
	if (mWindow)
	{
		SDL_FillRect(mWindowSurface, nullptr, mClearColor.GetPixelColor());
	}
}