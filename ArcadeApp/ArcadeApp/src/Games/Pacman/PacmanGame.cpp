#include "PacmanGame.h"
#include "App.h"

void PacmanGame::Init(GameController& gameController)
{
	mLevel.Init(App::Singletone().GetBasePath() + "src/Assets/Pacman_level.txt");
}

void PacmanGame::Update(uint32_t dt)
{
	mLevel.Update(dt);
}

void PacmanGame::Draw(Screen& screen)
{
	mLevel.Draw(screen);
}

const std::string& PacmanGame::GetName() const
{
	static std::string name = "Pacman";
	return name;
}

