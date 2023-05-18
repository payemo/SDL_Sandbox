#pragma once

#include <string>
#include <map>
#include "SDL.h"
#include "SDL_image.h"

class TextureManager
{
public:
	static TextureManager* Instance();

public:
		~TextureManager();

		bool Load(const std::string& fileName, const std::string& id, SDL_Renderer& renderer);

		void Draw(const std::string& id, int x, int y, int w, int h, SDL_Renderer& renderer, SDL_RendererFlip flipOption = SDL_FLIP_NONE);

		void DrawFrame(
			const std::string& id,
			int x,
			int y,
			int w,
			int h,
			int currentRow,
			int currentFrame,
			SDL_Renderer& renderer,
			SDL_RendererFlip flipOption = SDL_FLIP_NONE);

		void ClearFromTextureMap(const std::string& id);

private:
		TextureManager() {}

private:
		static TextureManager* instance;

private:
		std::map<std::string, SDL_Texture*> texture_map;
};

typedef TextureManager TheTextureManager;