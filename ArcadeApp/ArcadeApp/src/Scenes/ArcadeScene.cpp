#include <iostream>
#include "Screen.h"
#include "ArcadeScene.h"
#include "GameController.h"
#include "App.h"
#include "GameScene.h"
#include "BreakOut.h"
#include "NotImplementedScene.h"
#include "PacmanStartScene.h"

ArcadeScene::ArcadeScene() :
	ButtonOptionsScene({ "Tetris", "Break Out!", "Asteroids", "Pac-man" }, Color::Cyan())
{
}

void ArcadeScene::Init()
{
	std::vector<Button::ButtonAction> actions;

	actions.push_back([this] {
		App::Singletone().PushScene(GetScene(TETRIS));
	});
	actions.push_back([this] {
		App::Singletone().PushScene(GetScene(BREAK_OUT));
	});
	actions.push_back([this] {
		App::Singletone().PushScene(GetScene(ASTEROIDS));
	});
	actions.push_back([this] {
		App::Singletone().PushScene(GetScene(PACMAN));
	});

	SetButtonActions(actions);

	ButtonOptionsScene::Init();
}

void ArcadeScene::Update(uint32_t dt)
{
}

void ArcadeScene::Draw(Screen& screen)
{
	ButtonOptionsScene::Draw(screen);
}

const std::string& ArcadeScene::GetSceneName() const
{
	static std::string sceneName = "Arcade";
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
		std::unique_ptr<BreakOut> breakOutGame = std::make_unique<BreakOut>();
		std::unique_ptr<GameScene> breakOutScene = std::make_unique<GameScene>(std::move(breakOutGame));

		return breakOutScene;
	}
	break;

	case ASTEROIDS:
	{

	}
	break;

	case PACMAN:
	{
		return std::make_unique<PacmanStartScene>();
	}
	break;
	}

	std::unique_ptr<Scene> notImplementedScene = std::make_unique<NotImplementedScene>();

	return notImplementedScene;
}