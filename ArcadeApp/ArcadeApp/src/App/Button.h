#pragma once

#include <string>
#include "AARectangle.h"
#include <functional>
#include "Color.h"
#include "BitmapFont.h"

class Screen;

class Button
{
public:
	using ButtonAction = std::function<void(void)>;

	Button(const BitmapFont& bitmapFont, const Color& textColor, const Color& highlightColor = Color::White());
	void Init(Vec2D topLeft, unsigned int width, unsigned height);
	void Draw(Screen& screen);
	void ExecuteAction();

	inline void SetButtonText(const std::string& text) { mTitle = text; }
	inline const std::string& GetButtonText() const { return mTitle; }
	inline void SetHighlighted(bool highlighted) { mHighlighted = highlighted; }
	inline bool const IsHighlighted() const { return mHighlighted; }
	inline void SetButttonAction(Button::ButtonAction action) { mAction = action; }

private:
	const BitmapFont& mBitmapFont;
	std::string mTitle{ "" };
	AARectangle mBox;

	bool mHighlighted{ false };
	ButtonAction mAction{ nullptr };
	Color mHighlightColor;
	Color mTextColor;
};