#include <SDL2/SDL.h>
#include <iostream>
#include <cassert>
#include "App.h"
#include "ArcadeScene.h"

App* App::mInstance = nullptr;

App& App::Singletone()
{
	if (mInstance == nullptr)
	{
		mInstance = new App;
	}
	return *mInstance;
}

bool App::Init(uint32_t width, uint32_t height, uint32_t mag)
{
	mWindow = mScreen.Init(width, height, mag);

	std::unique_ptr<ArcadeScene> arcadeScene = std::make_unique<ArcadeScene>();
	PushScene(std::move(arcadeScene));

	return mWindow != nullptr;
}

void App::Run()
{
	if (mWindow)
	{
		SDL_Event event;
		bool running = true;

		uint32_t lastTick = SDL_GetTicks();
		uint32_t currTick = lastTick;

		uint32_t deltaTime = 10; // milliseconds
		uint32_t accumulator = 0;

		while (running)
		{
			currTick = SDL_GetTicks();
			// get interval between frames updation
			uint32_t frameTime = currTick - lastTick;

			if (frameTime > 300)
			{
				frameTime = 300;
			}
			lastTick = currTick;
			accumulator += frameTime;

			// Input
			while (SDL_PollEvent(&event))
			{
				if (event.key.keysym.sym == SDLK_ESCAPE || event.type == SDL_QUIT)
				{
					running = false;
					break;
				}
			}

			Scene* topScene = App::TopScene();
			assert(topScene && "App::TopScene()");

			if (topScene)
			{
				// Update state
				while (accumulator >= deltaTime)
				{
					// Update current scene by delta time.
					topScene->Update(deltaTime);
					std::cout << "Delta time step: " << deltaTime << std::endl;
					accumulator -= deltaTime;
				}

				// Render
				topScene->Draw(mScreen);
			}

			mScreen.SwapScreens();
		}
	}
}

void App::PushScene(std::unique_ptr<Scene> scene)
{
	assert(scene != nullptr);

	if (scene)
	{
		scene->Init();
		mSceneStack.emplace_back(std::move(scene));
		SDL_SetWindowTitle(mWindow, TopScene()->GetSceneName().c_str());
	}
}

void App::PopScene()
{
	if (mSceneStack.size() > 1)
	{
		mSceneStack.pop_back();
	}

	if (TopScene())
	{
		SDL_SetWindowTitle(mWindow, TopScene()->GetSceneName().c_str());
	}
}

Scene* App::TopScene()
{
	if (mSceneStack.empty())
	{
		return nullptr;
	}

	return mSceneStack.back().get();
}