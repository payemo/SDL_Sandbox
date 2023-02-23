#pragma once

#include "BreakOutGameLevel.h"
#include "Ball.h"

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

		if (!block.IsDestroyed() && block.HasCollided(ball.GetBoundingRect(), edge))
		{
			collidedBlocks.push_back(block);

			float mag = block.GetCollisionOffset(ball.GetBoundingRect()).Mag();

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

		if (block.HasCollided(ball.GetBoundingRect(), edge))
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

	const int blockWidth = 16;
	const int blockHeight = 8;

	const int numBlocksAcross = ((int)boundary.GetWidth() - (2 * (blockWidth)) / blockWidth);
	const int numBlocksRows = 5;

	float startX = ((int)boundary.GetWidth() - (numBlocksAcross * (blockWidth + 1))) / 2;

	Color colors[numBlocksRows];
	colors[0] = Color::Red();
	colors[1] = Color::Magenta();
	colors[2] = Color::Yellow();
	colors[3] = Color::Green();
	colors[4] = Color::Cyan();

	for (int r = 0; r < numBlocksRows; ++r)
	{
		AARectangle blockRect = { Vec2D(startX, blockHeight * (r + 1)), blockWidth, blockHeight };

		for (int c = 0; c < numBlocksAcross; ++c)
		{
			Block b;
			b.Init(blockRect, 1, Color::Black(), colors[r]);
			mBlocks.push_back(b);
			blockRect.MoveBy(Vec2D(blockWidth, 0));
		}
	}
}