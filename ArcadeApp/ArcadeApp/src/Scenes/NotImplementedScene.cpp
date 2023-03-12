#include "NotImplementedScene.h"
#include "App.h"
#include "AARectangle.h"
#include "InputAction.h"
#include "Screen.h"

void NotImplementedScene::Init()
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
};

void NotImplementedScene::Update(uint32_t dt)
{

};

void NotImplementedScene::Draw(Screen& screen)
{
	const BitmapFont& font = App::Singletone().GetFont();

	AARectangle rect = { Vec2D::Zero, App::Singletone().Width(), App::Singletone().Height() };

	Vec2D textDrawPos = font.GetDrawPosition(GetSceneName(), rect, BFXA_CENTER, BFYA_CENTER);

	screen.Draw(font, GetSceneName(), textDrawPos, Color::Red());
};

const std::string& NotImplementedScene::GetSceneName() const
{
	static std::string name = "Not Implemented!";
	return name;
};