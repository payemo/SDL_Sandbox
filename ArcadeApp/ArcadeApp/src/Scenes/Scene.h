#pragma once

#include <string>
#include <stdint.h>

class Screen;

// Interface for all application scenes
class Scene
{
public:
	virtual ~Scene() {}
	virtual void Init() = 0;
	virtual void Update(uint32_t dt) = 0;
	virtual void Draw(Screen& screen) = 0;
	virtual const std::string& GetSceneName() const = 0;
};