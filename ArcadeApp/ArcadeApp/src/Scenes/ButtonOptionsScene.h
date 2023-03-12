#pragma once

#include "Scene.h"
#include "Button.h"
#include <string>
#include <vector>

class Screen;

class ButtonOptionsScene : public Scene
{
public:
	ButtonOptionsScene(const std::vector<std::string>& optionNames, const Color& textColor);

	void SetButtonActions(const std::vector<Button::ButtonAction>& buttonActions);

	virtual void Init() override;
	virtual void Update(uint32_t dt) override;
	virtual void Draw(Screen& screen) override;

private:
	void SetNextButtonHighlighted();
	void HighlightCurrentButton();
	void SetPreviousButtonHighlighted();
	void ExecuteCurrentButtonAction();

	std::vector<Button> mButtons;
	int mHighlightedOption{ 0 };
};