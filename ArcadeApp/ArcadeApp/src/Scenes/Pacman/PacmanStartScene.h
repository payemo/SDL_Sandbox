#pragma once

#include "ButtonOptionsScene.h"

class PacmanStartScene : public ButtonOptionsScene
{
public:
	PacmanStartScene();

	void Init() override;
	void Update(uint32_t dt) override;
	void Draw(Screen& screen) override;
	const std::string& GetSceneName() const override;
};