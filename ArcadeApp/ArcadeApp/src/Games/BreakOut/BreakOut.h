#pragma once

#include "Game.h"

class BreakOut : public Game
{
public:
	virtual void Init(GameController& gameController) override;
	virtual void Update(uint32_t dt) override;
	virtual void Draw(Screen& screen) override;
	virtual const std::string& GetName() const override;
};