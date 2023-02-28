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
	size_t imgBufferSize = mWidth * mHeight;
	
	mPixels.reserve(imgBufferSize);

	SDL_LockSurface(bmpSurface);

	uint32_t* pixels = static_cast<uint32_t*>(bmpSurface->pixels);

	for (int i = 0; i < imgBufferSize; ++i)
	{
		mPixels.push_back(Color(pixels[i]));
	}

	SDL_UnlockSurface(bmpSurface);
	SDL_FreeSurface(bmpSurface);

	return true;
}