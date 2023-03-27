#include "PacmanLevel.h"
#include "FileCommandLoader.h"
#include "Screen.h"

bool PacmanLevel::Init(const std::string& levelPath)
{

	return LoadLevel(levelPath);
}

void PacmanLevel::Update(uint32_t dt)
{

}

void PacmanLevel::Draw(Screen& screen)
{
	for (const auto& wall : mWalls)
	{
		screen.Draw(wall.GetRectangle(), Color::Blue());
	}
}

// privatte

bool PacmanLevel::LoadLevel(const std::string& levelPath)
{
	FileCommandLoader fileLoader;

	Command tileWidthCommand;
	tileWidthCommand.command = "tile_width";
	tileWidthCommand.parseFunc = [this](ParseFuncParams params) {
		mTiles.back().width = FileCommandLoader::ReadInt(params);
	};

	fileLoader.AddCommand(tileWidthCommand);

	Command tileHeightCommand;
	tileHeightCommand.command = "tile_height";
	tileHeightCommand.parseFunc = [this](ParseFuncParams params) {
		mTileHeight = FileCommandLoader::ReadInt(params);
	};

	fileLoader.AddCommand(tileHeightCommand);

	Command tileCommand;
	tileCommand.command = "tile";
	tileCommand.parseFunc = [this](ParseFuncParams params) {
		mTiles.push_back(Tile());
	};

	fileLoader.AddCommand(tileCommand);

	Command tileSymbolCommand;
	tileSymbolCommand.command = "tile_symbol";
	tileSymbolCommand.parseFunc = [this](ParseFuncParams params) {
		mTiles.back().symbol = FileCommandLoader::ReadChar(params);
	};

	fileLoader.AddCommand(tileSymbolCommand);

	Command tileCollisionCommand;
	tileCollisionCommand.command = "tile_collision";
	tileCollisionCommand.parseFunc = [this](ParseFuncParams params) {
		mTiles.back().collidable = FileCommandLoader::ReadInt(params);
	};

	fileLoader.AddCommand(tileCollisionCommand);

	Vec2D layoutOffset;

	Command layoutOffsetCommand;
	layoutOffsetCommand.command = "layout_offset";
	layoutOffsetCommand.parseFunc = [&layoutOffset, this](ParseFuncParams params) {
		mLayoutOffset = FileCommandLoader::ReadSize(params);
		layoutOffset = mLayoutOffset;
	};

	fileLoader.AddCommand(layoutOffsetCommand);

	Command layoutCommand;
	layoutCommand.command = "layout";
	layoutCommand.type = COMMAND_MULTI_LINE;
	layoutCommand.parseFunc = [&layoutOffset, this](ParseFuncParams params) {
		int startingX = layoutOffset.GetX();

		for (int i = 0; i < params.line.length(); ++i)
		{
			Tile* tile = GetTileBySymbol(params.line[i]);

			if (tile)
			{
				tile->pos = Vec2D(startingX, layoutOffset.GetY());

				if (tile->collidable > 0)
				{
					Excluder wall;
					wall.Init(AARectangle(Vec2D(startingX, layoutOffset.GetY()), tile->width, static_cast<int>(mTileHeight)));

					mWalls.push_back(wall);
				}

				startingX += tile->width;
			}
		}

		layoutOffset += Vec2D(0, mTileHeight);
	};

	fileLoader.AddCommand(layoutCommand);

	return fileLoader.LoadFile(levelPath);
}

PacmanLevel::Tile* PacmanLevel::GetTileBySymbol(char symbol)
{
	for (int i = 0; i < mTiles.size(); ++i) 
	{
		if (mTiles[i].symbol == symbol)
		{
			return &mTiles[i];
		}
	}

	return nullptr;
}