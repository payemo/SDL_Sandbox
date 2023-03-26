#pragma once

#include "Game.h"

class PacmanGame : public Game
{
public:
	void Init(GameController& gameController) override;
	void Update(uint32_t dt) override;
	void Draw(Screen& screen) override;
	const std::string& GetName() const override;
};