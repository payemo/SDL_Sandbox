#pragma once

#include "Screen.h"
#include "Scene.h"
#include <stdint.h>
#include <vector>
#include "InputController.h"
#include "BitmapFont.h"

struct SDL_Window;
class Scene;

class App
{
public:
	static App& Singletone();
	bool Init(uint32_t width, uint32_t height, uint32_t mag);
	void Run();

	inline uint32_t Width() const { return mScreen.Width(); }
	inline uint32_t Height() const { return mScreen.Height(); }

	void PushScene(std::unique_ptr<Scene> scene);
	void PopScene();
	Scene* TopScene(); // current scene

	static const std::string& GetBasePath();

	inline const BitmapFont& GetFont() const { return mFont; }

protected:
	App() {}

private:
	static App* mInstance;

	Screen mScreen;
	SDL_Window* mWindow;

	std::vector<std::unique_ptr<Scene>> mSceneStack;
	InputController mInputController;
	BitmapFont mFont;
};