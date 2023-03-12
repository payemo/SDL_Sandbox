#include "Button.h"
#include "Screen.h"

Button::Button(const BitmapFont& bitmapFont, const Color& textColor, const Color& highlightColor)
	: mBitmapFont(bitmapFont), 
	mTextColor(textColor), 
	mHighlightColor(highlightColor)
{

}

void Button::Init(Vec2D topLeft, unsigned int width, unsigned height)
{
	mBox = AARectangle(topLeft, width, height);
}

void Button::Draw(Screen& screen)
{
	screen.Draw(mBitmapFont, mTitle, mBitmapFont.GetDrawPosition(mTitle, mBox, BFXA_CENTER, BFYA_CENTER), mTextColor);

	if (mHighlighted)
	{
		screen.Draw(mBox, mHighlightColor);
	}
}

void Button::ExecuteAction()
{
	mAction();
}