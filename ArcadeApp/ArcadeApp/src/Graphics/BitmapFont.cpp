#include "BitmapFont.h"
#include "AARectangle.h"
#include "Vec2D.h"

bool BitmapFont::Load(const std::string& path)
{
	return mFontSheet.Load(path);
}

Size BitmapFont::GetSizeOf(const std::string& str) const
{
	Size textSize;

	size_t length = str.length();

	int i = 0;
	for (auto c : str)
	{
		if (c == ' ')
		{
			textSize.width += GetFontSpacingBetweenWords();
			++i;
			continue;
		}

		Sprite sprite = mFontSheet.GetSprite(std::string("") + c);
		textSize.height = std::max(sprite.height, textSize.height);
		textSize.width += sprite.width;

		if (i + 1 < length)
		{
			textSize.width += GetFontSpacingBetweenLetters();
		}

		++i;
	}

	return textSize;
}

Vec2D BitmapFont::GetDrawPosition(const std::string& str, const AARectangle& box, BitmapFontXAlignment xAlignment, BitmapFontYAlignment yAlignment) const
{
	Size textSize = GetSizeOf(str);

	uint32_t x = 0;
	uint32_t y = 0;

	if (xAlignment == BFXA_CENTER)
	{
		x = box.GetWidth() / 2 - textSize.width / 2;
	}
	else if (xAlignment == BFXA_RIGHT)
	{
		x = box.GetWidth() - textSize.width;
	}

	x += box.GetTopLeftPoint().GetX();

	if (yAlignment == BFYA_CENTER)
	{
		y = box.GetHeight() / 2 - textSize.height / 2;
	}
	else if (yAlignment == BFYA_BOTTOM)
	{
		y = box.GetHeight() - textSize.height;
	}

	y += box.GetTopLeftPoint().GetY();

	return Vec2D(x, y);
;}