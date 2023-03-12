#include "ButtonOptionsScene.h"
#include "App.h"
#include "BitmapFont.h"
#include "Utils.h"

ButtonOptionsScene::ButtonOptionsScene(const std::vector<std::string>& optionNames, const Color& textColor)
{
	const BitmapFont& font = App::Singletone().GetFont();

	for (int i = 0; i < optionNames.size(); ++i)
	{
		mButtons.push_back(Button(font, textColor));
		mButtons.back().SetButtonText(optionNames[i]);
	}

	if (optionNames.size())
	{
		mButtons[mHighlightedOption].SetHighlighted(true);
	}
}

void ButtonOptionsScene::SetButtonActions(const std::vector<Button::ButtonAction>& buttonActions)
{
	for (int i = 0; i < mButtons.size(); ++i)
	{
		mButtons[i].SetButttonAction(buttonActions[i]);
	}
}

void ButtonOptionsScene::SetNextButtonHighlighted()
{
	mHighlightedOption = (mHighlightedOption + 1) % mButtons.size();

	HighlightCurrentButton();
}

void ButtonOptionsScene::HighlightCurrentButton()
{
	for (auto& button : mButtons)
	{
		button.SetHighlighted(false);
	}

	mButtons[mHighlightedOption].SetHighlighted(true);
}

void ButtonOptionsScene::SetPreviousButtonHighlighted()
{
	--mHighlightedOption;

	if (mHighlightedOption < 0)
	{
		mHighlightedOption = static_cast<int>(mButtons.size()) - 1;
	}

	HighlightCurrentButton();
}

void ButtonOptionsScene::ExecuteCurrentButtonAction()
{
	mButtons[mHighlightedOption].ExecuteAction();
}

void ButtonOptionsScene::Init()
{
	ButtonAction upAction;
	upAction.key = GameController::UpKey();
	upAction.action = [this](uint32_t dt, InputState state)
	{
		if (GameController::IsPressed(state))
		{
			SetPreviousButtonHighlighted();
		}
	};

	mGameController.AddInputAction(upAction);

	ButtonAction downAction;
	downAction.key = GameController::DownKey();
	downAction.action = [this](uint32_t dt, InputState state)
	{
		if (GameController::IsPressed(state))
		{
			SetNextButtonHighlighted();
		}
	};

	mGameController.AddInputAction(downAction);

	ButtonAction execAction;
	execAction.key = GameController::ActionKey();
	execAction.action = [this](uint32_t dt, InputState state)
	{
		if (GameController::IsPressed(state))
		{
			ExecuteCurrentButtonAction();
		}
	};

	mGameController.AddInputAction(execAction);

	uint32_t height = App::Singletone().Height();
	uint32_t width = App::Singletone().Width();

	const BitmapFont& font = App::Singletone().GetFont();

	Size fontSize = font.GetSizeOf(mButtons[0].GetButtonText());

	const int buttonPad = 10;

	unsigned int buttonHeight = fontSize.height + buttonPad * 2;

	uint32_t maxButtonWidth = fontSize.width;

	for (auto& button : mButtons)
	{
		Size s = font.GetSizeOf(button.GetButtonText());

		if (s.width > maxButtonWidth)
		{
			maxButtonWidth = s.width;
		}
	}

	maxButtonWidth += buttonPad * 2;

	const uint32_t yPad = 1;
	uint32_t yOffset = height / 2 - ((buttonHeight + yPad) * static_cast<uint32_t>(mButtons.size())) / 2;

	for (auto& button : mButtons)
	{
		button.Init(Vec2D(width / 2 - maxButtonWidth / 2, yOffset), maxButtonWidth, buttonHeight);

		yOffset += buttonHeight + yPad;
	}

	mButtons[mHighlightedOption].SetHighlighted(true);
}

void ButtonOptionsScene::Update(uint32_t dt)
{

}

void ButtonOptionsScene::Draw(Screen& screen)
{
	for (auto& button : mButtons)
	{
		button.Draw(screen);
	}
}