#include <iostream>
#include "ArcadeScene.h"
#include "Screen.h"
#include "Line2D.h"
#include "AARectangle.h"
#include "Triangle.h"
#include "Circle.h"
#include "Color.h"
#include "GameController.h"
#include "App.h"

ArcadeScene::ArcadeScene()
{
}

void ArcadeScene::Init()
{
	ButtonAction action;
	action.key = GameController::ActionKey();
	action.action = [](uint32_t dt, InputState state)
	{
		if (GameController::IsPressed(state))
		{
			std::cout << "Action button was pressed." << std::endl;
		}
	};

	mGameController.AddInputAction(action);

	MouseButtonAction mouseAction;
	mouseAction.button = GameController::LeftMouseButton();
	mouseAction.inputAction = [](InputState state, const MousePosition& mousePos)
	{
		if (GameController::IsPressed(state))
		{
			std::cout << "Mouse button was pressed." << std::endl;
		}
	};

	mGameController.AddMouseButtonAction(mouseAction);
	mGameController.SetMouseMovedAction([](const MousePosition& mousePos) {
		std::cout << "Mouse X position: " << mousePos.xPos << ", mouse Y position: " << mousePos.yPos << std::endl;
	});
}

void ArcadeScene::Update(uint32_t dt)
{

}

void ArcadeScene::Draw(Screen& screen)
{
	const BitmapFont& font = App::Singletone().GetFont();

	AARectangle rect = { Vec2D::Zero, App::Singletone().Width(), App::Singletone().Height() };
	Vec2D textDrawPosition = font.GetDrawPosition(GetSceneName(), rect, BFXA_CENTER, BFYA_CENTER);

	screen.Draw(font, GetSceneName(), textDrawPosition);
}

const std::string& ArcadeScene::GetSceneName() const
{
	static std::string sceneName = "Arcade Scene";
	return sceneName;
}

std::unique_ptr<Scene> ArcadeScene::GetScene(GameSelector game)
{
	switch (game)
	{
	case TETRIS:
	{

	}
	break;

	case BREAK_OUT:
	{

	}
	break;

	case ASTEROIDS:
	{

	}
	break;

	case PACMAN:
	{

	}
	break;
	default:
	{

	}
	break;
	}

	return nullptr;
}