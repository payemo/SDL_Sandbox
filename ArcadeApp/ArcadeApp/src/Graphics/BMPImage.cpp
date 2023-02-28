#include "BMPImage.h"
#include <SDL2/SDL.h>
#include <algorithm>

BMPImage::BMPImage()
{

}

bool BMPImage::Load(const std::string& path)
{
	SDL_Surface* bmpSurface = SDL_LoadBMP(path.c_str());

	if (bmpSurface == nullptr)
	{
		return false;
	}

	mWidth = bmpSurface->w;
	mHeight = bmpSurface->h;
	
	mPixels.reserve(mWidth * mHeight);

	SDL_LockSurface(bmpSurface);

	uint32_t* pixels = static_cast<uint32_t*>(bmpSurface->pixels);

	for (int i = 0; i < mPixels.size(); ++i)
	{
		mPixels.push_back(Color(pixels[i]));
	}

	SDL_UnlockSurface(bmpSurface);
	SDL_FreeSurface(bmpSurface);

	return true;
}