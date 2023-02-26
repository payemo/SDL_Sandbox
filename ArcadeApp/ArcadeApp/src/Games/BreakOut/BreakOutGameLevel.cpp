#pragma once

#include "BreakOutGameLevel.h"
#include "Ball.h"
#include "App.h"
#include "FileCommandLoader.h"

struct LayoutBlock
{
	char symbol = '-';
	int hp = 0;
	Color color = Color::Black();
};

LayoutBlock FindLayoutBlockForSymbol(const std::vector<LayoutBlock>& blocks, char symbol)
{
	for (size_t i = 0; i < blocks.size(); ++i)
	{
		if (blocks[i].symbol == symbol)
		{
			return blocks[i];
		}
	}

	return LayoutBlock();
}

BreakOutGameLevel::BreakOutGameLevel()
{

}

void BreakOutGameLevel::Init(const AARectangle& boundary)
{
	CreateDefaultLevel(boundary);
}

void BreakOutGameLevel::Load(const std::vector<Block>& blocks)
{
	mBlocks.clear();
	mBlocks = blocks;
}

void BreakOutGameLevel::Update(uint32_t dt, Ball& ball)
{
	std::vector<Block> collidedBlocks;

	BoundaryEdge edgeToBounceOffOf;
	Block* blockToBounceOffOf = nullptr;

	float largestMag = -1.0f;

	for (auto& block : mBlocks)
	{
		BoundaryEdge edge;
		auto ballRect = ball.GetBoundingRect();

		if (!block.IsDestroyed() && block.HasCollided(ballRect, edge))
		{
			collidedBlocks.push_back(block);

			float mag = block.GetCollisionOffset(ballRect).Mag();

			if (mag > largestMag)
			{
				edgeToBounceOffOf = edge;
				blockToBounceOffOf = &block;
			}
		}
	}

	if (blockToBounceOffOf != nullptr)
	{
		blockToBounceOffOf->Bounce(ball, edgeToBounceOffOf);
		blockToBounceOffOf->ReduceHP();
	}

	for (const auto& block : collidedBlocks)
	{
		BoundaryEdge edge;
		auto ballRect = ball.GetBoundingRect();

		if (block.HasCollided(ballRect, edge))
		{
			Vec2D p;
			ball.MakeFlushWithEdge(edge, p, true);
		}
	}
}

void BreakOutGameLevel::Draw(Screen& screen)
{
	for (auto& block : mBlocks)
	{
		if (!block.IsDestroyed())
		{
			block.Draw(screen);
		}
	}
}

void BreakOutGameLevel::CreateDefaultLevel(const AARectangle& boundary)
{
	mBlocks.clear();

	int boundaryWidth = static_cast<int>(boundary.GetWidth());

	const int numBlocksAcross = (boundaryWidth - (2 * BLOCK_WIDTH)) / BLOCK_WIDTH;
	const int numBlocksRows = 5;

	float startX = ((int)boundary.GetWidth() - (numBlocksAcross * (BLOCK_WIDTH + 1))) / 2;

	Color colors[numBlocksRows];
	colors[0] = Color::Red();
	colors[1] = Color::Magenta();
	colors[2] = Color::Yellow();
	colors[3] = Color::Green();
	colors[4] = Color::Cyan();

	for (int r = 0; r < numBlocksRows; ++r)
	{
		AARectangle blockRect = { Vec2D(startX, BLOCK_HEIGHT * (r + 1)), BLOCK_WIDTH, BLOCK_HEIGHT };

		for (int c = 0; c < numBlocksAcross; ++c)
		{
			Block b;
			b.Init(blockRect, 1, Color::Black(), colors[r]);
			mBlocks.push_back(b);
			blockRect.MoveBy(Vec2D(BLOCK_WIDTH, 0));
		}
	}
}

bool BreakOutGameLevel::IsLevelComplete() const
{
	for (size_t i = 0; i < mBlocks.size(); ++i)
	{
		if (!mBlocks[i].IsDestroyed() && mBlocks[i].GetHP() != Block::UNBREAKABLE)
		{
			return false;
		}
	}

	return true;
}

std::vector<BreakOutGameLevel> BreakOutGameLevel::LoadLevelsFromFile(const std::string filePath)
{
	std::vector<BreakOutGameLevel> levels;

	std::vector<LayoutBlock> layoutBlocks;

	std::vector<Block> levelBlocks;

	int width = 0;
	int height = 0;

	FileCommandLoader fileLoader;

	Command levelCommand;

	levelCommand.command = "level";
	levelCommand.parseFunc = [&](ParseFuncParams params) {
		if (levels.size() > 0)
		{
			levels.back().Load(levelBlocks);
		}
		layoutBlocks.clear();
		levelBlocks.clear();
		width = 0;
		height = 0;

		BreakOutGameLevel level;
		level.Init(AARectangle(Vec2D::Zero, App::Singletone().Width(), App::Singletone().Height()));

		levels.push_back(level);
	};

	fileLoader.AddCommand(levelCommand);

	Command blockCommand;
	blockCommand.command = "block";
	blockCommand.parseFunc = [&](ParseFuncParams params) {
		LayoutBlock lb;

		layoutBlocks.push_back(lb);
	};

	fileLoader.AddCommand(blockCommand);

	Command symbolCommand;
	symbolCommand.command = "symbol";
	symbolCommand.parseFunc = [&](ParseFuncParams params) {
		layoutBlocks.back().symbol = FileCommandLoader::ReadChar(params);
	};

	fileLoader.AddCommand(symbolCommand);

	Command fillColorCommand;
	fillColorCommand.command = "fillcolor";
	fillColorCommand.parseFunc = [&](ParseFuncParams params) {
		layoutBlocks.back().color = FileCommandLoader::ReadColor(params);
	};

	fileLoader.AddCommand(fillColorCommand);

	Command hpCommand;
	hpCommand.command = "hp";
	hpCommand.parseFunc = [&](ParseFuncParams params) {
		layoutBlocks.back().hp = FileCommandLoader::ReadInt(params);
	};

	fileLoader.AddCommand(hpCommand);

	Command widthCommand;
	widthCommand.command = "width";
	widthCommand.parseFunc = [&](ParseFuncParams params) {
		width = FileCommandLoader::ReadInt(params);
	};

	fileLoader.AddCommand(widthCommand);

	Command heightCommand;
	heightCommand.command = "height";
	heightCommand.parseFunc = [&](ParseFuncParams params) {
		height = FileCommandLoader::ReadInt(params);
	};

	fileLoader.AddCommand(heightCommand);

	Command layoutCommand;
	layoutCommand.type = COMMAND_MULTI_LINE;
	layoutCommand.command = "layout";
	layoutCommand.parseFunc = [&](ParseFuncParams params) {

		float startingX = 0;
		AARectangle blockRect(Vec2D(startingX, (params.lineNum + 1) * BLOCK_HEIGHT), BLOCK_WIDTH, BLOCK_HEIGHT);

		for (int c = 0; c < params.line.length(); ++c)
		{
			if (params.line[c] != '-')
			{
				LayoutBlock layoutBlock = FindLayoutBlockForSymbol(layoutBlocks, params.line[c]);

				Block b;
				b.Init(blockRect, layoutBlock.hp, Color::Black(), layoutBlock.color);
				levelBlocks.push_back(b);
			}
			blockRect.MoveBy(Vec2D(BLOCK_WIDTH, 0));
		}
	};


	fileLoader.AddCommand(layoutCommand);

	fileLoader.LoadFile(filePath);

	if (levels.size() > 0)
	{
		levels.back().Load(levelBlocks);
	}

	return levels;
}