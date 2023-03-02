#pragma once

#include "BMPImage.h"
#include <string>
#include <vector>
#include <stdint.h>
#include <memory>

struct Sprite
{
	uint32_t xPos = 0;
	uint32_t yPos = 0;
	uint32_t width = 0;
	uint32_t height = 0;
};

class SpriteSheet
{
public:
	SpriteSheet();

	bool Load(const std::string& name);
	Sprite GetSprite(const std::string& spriteName) const;

	std::vector<std::string>& GetSpriteNames() const;

	inline const BMPImage& GetBMPImage() const { return *mBmpImage; }
	inline uint32_t GetWidth() const { return mBmpImage->GetWidth(); }
	inline uint32_t GetHeight() const { return mBmpImage->GetHeight(); }

private:
	bool LoadSpriteSections(const std::string& path);

	struct BMPImageSection
	{
		std::string key = "";
		Sprite sprite;
	};

	std::unique_ptr<BMPImage> mBmpImage{ std::make_unique<BMPImage>() };
	std::vector<BMPImageSection> mSections;
};