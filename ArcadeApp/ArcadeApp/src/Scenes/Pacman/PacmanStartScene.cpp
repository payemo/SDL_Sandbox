#include "PacmanStartScene.h"
#include "App.h"
#include "NotImplementedScene.h"
#include "GameScene.h"
#include "PacmanGame.h"
#include "vector"
#include <memory>

PacmanStartScene::PacmanStartScene() : ButtonOptionsScene({ "Play Game", "High Scores" }, Color::Yellow())
{

}

void PacmanStartScene::Init()
{
	ButtonAction backAction;
	backAction.key = GameController::CancelKey();
	backAction.action = [this](uint32_t dt, InputState state)
	{
		if (GameController::IsPressed(state))
		{
			App::Singletone().PopScene();
		}
	};

	mGameController.AddInputAction(backAction);

	std::vector<Button::ButtonAction> actions;

	actions.push_back([this]() {
		auto pacmanGame = std::make_unique<PacmanGame>();
		App::Singletone().PushScene(std::make_unique<GameScene>(std::move(pacmanGame)));
	});

	actions.push_back([this]() {
		App::Singletone().PushScene(std::make_unique<NotImplementedScene>());
	});

	SetButtonActions(actions);

	ButtonOptionsScene::Init();
}

void PacmanStartScene::Update(uint32_t dt)
{

}

void PacmanStartScene::Draw(Screen& screen)
{
	ButtonOptionsScene::Draw(screen);
}

const std::string& PacmanStartScene::GetSceneName() const
{
	static std::string name = "Pacman Start";
	return name;
}