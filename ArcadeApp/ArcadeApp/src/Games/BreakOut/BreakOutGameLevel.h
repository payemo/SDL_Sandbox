#pragma once

#include "Block.h"
#include <vector>
#include <stdint.h>

class Screen;
class Ball;
class AARectangle;

class BreakOutGameLevel
{
public:
	BreakOutGameLevel();
	void Init(const AARectangle& boundary);
	void Load(const std::vector<Block>& blocks);
	void Update(uint32_t dt, Ball& ball);
	void Draw(Screen& screen);

private:
	void CreateDefaultLevel(const AARectangle& boundary);
	std::vector<Block> mBlocks;
};