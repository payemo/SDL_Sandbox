#pragma once

#include <stdint.h>
#include "ScreenBuffer.h"
#include "Color.h"

class Vec2D;

struct SDL_Window;
struct SDL_Surface;

class Screen
{
public:
	Screen();
	Screen(const Screen& other) = delete;
	~Screen();

	SDL_Window* Init(uint32_t w, uint32_t h, uint32_t mag);
	void SwapScreens();

	inline void SetClearColor(const Color& clearColor) { mClearColor = clearColor; }
	inline uint32_t Width() const { return mWidth; }
	inline uint32_t Height() const { return mHeight; }

	// Draw methods
	void Draw(int x, int y, const Color& color);
	void Draw(const Vec2D& point, const Color& color);

	Screen& operator=(const Screen& screen) = delete;
 
private:
	void ClearScreen();

	uint32_t mWidth;
	uint32_t mHeight;

	Color mClearColor;
	ScreenBuffer mBackBuffer;

	SDL_Window* mWindow;
	SDL_Surface* mWindowSurface;
};