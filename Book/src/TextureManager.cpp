#include "TextureManager.h"

TextureManager::~TextureManager()
{
		for (auto it = texture_map.begin(); it != texture_map.end(); ++it) {
			delete it->second;
		}
		texture_map.clear();
}

TextureManager* TextureManager::instance = nullptr;

TextureManager* TextureManager::Instance()
{
		if (!instance) {
			instance = new TextureManager;
		}
		return instance;
}

bool TextureManager::Load(const std::string& fileName, const std::string& id, SDL_Renderer& renderer)
{
		SDL_Surface* tmpSurface = IMG_Load(fileName.c_str());

		if (!tmpSurface)
			return false;

		SDL_Texture* texture = SDL_CreateTextureFromSurface(&renderer, tmpSurface);

		SDL_FreeSurface(tmpSurface);

		if (texture) {
			texture_map[id] = texture;
			return true;
		}

		return false;
}

void TextureManager::Draw(const std::string& id, int x, int y, int w, int h, SDL_Renderer& renderer, SDL_RendererFlip flipOption)
{
		SDL_Rect srcRect, destRect;

		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.w = destRect.w = w;
		srcRect.h = destRect.h = h;
		destRect.x = x;
		destRect.y = y;

		SDL_RenderCopyEx(&renderer, texture_map[id], &srcRect, &destRect, 0, 0, flipOption);
}

void TextureManager::DrawFrame(
		const std::string& id,
		int x,
		int y,
		int w,
		int h,
		int currentRow,
		int currentFrame,
		SDL_Renderer& renderer,
		SDL_RendererFlip flipOption)
{
		SDL_Rect srcRect, destRect;
		srcRect.x = w * currentFrame;
		srcRect.y = h * (currentRow - 1);
		srcRect.w = w;
		srcRect.h = h;
		srcRect.w = destRect.w = w;
		srcRect.h = destRect.h = h;
		destRect.x = x;
		destRect.y = y;

		SDL_RenderCopyEx(&renderer, texture_map[id], &srcRect, &destRect, 0, 0, flipOption);
}

void TextureManager::DrawTile(
			const std::string& id,
			int margin,
			int spacing,
			int x,
			int y,
			int width,
			int height,
			int currentRow,
			int currentFrame,
			SDL_Renderer& renderer)
{
	SDL_Rect srcRect, destRect;
	srcRect.x = margin + (spacing + width) * currentFrame;
	srcRect.y = margin + (spacing + height) * currentRow;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(&renderer, texture_map[id], &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}

void TextureManager::ClearFromTextureMap(const std::string& id)
{
	texture_map.erase(id);
}