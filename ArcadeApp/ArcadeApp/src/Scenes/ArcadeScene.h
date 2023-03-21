#pragma once

#include "ButtonOptionsScene.h"
#include <memory>
#include "AnimationPlayer.h"

class Screen;

enum GameSelector
{
	TETRIS = 0,
	BREAK_OUT,
	ASTEROIDS,
	PACMAN,
	NUM_GAMES
};

class ArcadeScene : public ButtonOptionsScene
{
public:
	ArcadeScene();
	virtual void Init() override;
	virtual void Update(uint32_t dt) override;
	virtual void Draw(Screen& screen) override;
	virtual const std::string& GetSceneName() const override;

private:
	std::unique_ptr<Scene> GetScene(GameSelector game);

	AnimationPlayer mAnimationPlayer;
	SpriteSheet mSpriteSheet;
};