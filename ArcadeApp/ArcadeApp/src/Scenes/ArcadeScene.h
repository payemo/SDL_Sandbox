#pragma once

#include "Scene.h"
#include <memory>
#include "BMPImage.h"

class Screen;

enum GameSelector
{
	TETRIS = 0,
	BREAK_OUT,
	ASTEROIDS,
	PACMAN,
	NUM_GAMES
};

class ArcadeScene : public Scene
{
public:
	ArcadeScene();
	virtual void Init() override;
	virtual void Update(uint32_t dt) override;
	virtual void Draw(Screen& screen) override;
	virtual const std::string& GetSceneName() const override;

private:
	std::unique_ptr<Scene> GetScene(GameSelector game);

	// for testing purposes
	BMPImage mTempImage;
};