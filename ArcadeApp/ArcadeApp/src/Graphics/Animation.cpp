#include "Animation.h"
#include "FileCommandLoader.h"
#include <cassert>

Animation::Animation()
{

}

AnimationFrame Animation::GetAnimationFrame(uint32_t frameNum) const
{
	AnimationFrame frame;

	if (frameNum > NumFrames())
	{
		return frame;
	}

	frame.frame = mFrames[frameNum];

	if (frameNum < NumFrameColors())
	{
		frame.frameColor = mFrameColors[frameNum];
		frame.frameColorSet = 1;
	}

	if (mOverlay.size() > 0)
	{
		frame.overlay = mOverlay;
	}

	if (frameNum < NumOverlayColos())
	{
		frame.overlayColor = mOverlayColors[frameNum];
	}

	if (frameNum < NumFrameOffsets())
	{
		frame.offset = mFrameOffsets[frameNum];
	}

	frame.size = mSize;

	return frame;
}

std::vector<Animation> Animation::LoadAnimation(const std::string& filePath)
{
	std::vector<Animation> animations;

	FileCommandLoader fileLoader;

	Command animationCommand;
	animationCommand.command = "animation";
	animationCommand.parseFunc = [&](ParseFuncParams params) 
	{
		Animation newAnimation;
		newAnimation.SetName((FileCommandLoader::ReadString(params)));
		animations.push_back(newAnimation);
	};

	fileLoader.AddCommand(animationCommand);

	Command spriteSheetCommand;
	spriteSheetCommand.command = "sprite_sheet";
	spriteSheetCommand.parseFunc = [&](ParseFuncParams params)
	{
		animations.back().SetSpriteSheetName((FileCommandLoader::ReadString(params)));
	};

	fileLoader.AddCommand(spriteSheetCommand);

	Command sizeCommand;
	sizeCommand.command = "size";
	sizeCommand.parseFunc = [&](ParseFuncParams params)
	{
		animations.back().SetSize((FileCommandLoader::ReadSize(params)));
	};

	fileLoader.AddCommand(sizeCommand);

	Command fpsCommand;
	fpsCommand.command = "fps";
	fpsCommand.parseFunc = [&](ParseFuncParams params)
	{
		animations.back().SetFPS((FileCommandLoader::ReadInt(params)));
	};

	fileLoader.AddCommand(fpsCommand);

	Command framesCommand;
	framesCommand.command = "frame_keys";
	framesCommand.command = COMMAND_MULTI_LINE;
	framesCommand.parseFunc = [&](ParseFuncParams params)
	{
		animations.back().AddFrame(params.line);
	};

	fileLoader.AddCommand(framesCommand);

	Command overlayCommand;
	overlayCommand.command = "overlay";
	overlayCommand.parseFunc = [&](ParseFuncParams params)
	{
		animations.back().SetOverlay((FileCommandLoader::ReadString(params)));
	};

	fileLoader.AddCommand(overlayCommand);

	Command frameColorCommand;
	frameColorCommand.command = "frame_colors";
	frameColorCommand.command = COMMAND_MULTI_LINE;
	frameColorCommand.parseFunc = [&](ParseFuncParams params)
	{
		animations.back().AddFrameColor(FileCommandLoader::ReadColor(params));
	};

	fileLoader.AddCommand(frameColorCommand);

	Command overlayFrameColorCommand;
	overlayFrameColorCommand.command = "overlay_colors";
	overlayFrameColorCommand.command = COMMAND_MULTI_LINE;
	overlayFrameColorCommand.parseFunc = [&](ParseFuncParams params)
	{
		animations.back().AddOverlayFrameColor(FileCommandLoader::ReadColor(params));
	};

	fileLoader.AddCommand(overlayFrameColorCommand);

	Command frameOffsetsCommand;
	frameOffsetsCommand.command = "frame_offsets";
	frameOffsetsCommand.command = COMMAND_MULTI_LINE;
	frameOffsetsCommand.parseFunc = [&](ParseFuncParams params)
	{
		animations.back().AddFrameOffset(FileCommandLoader::ReadSize(params));
	};

	fileLoader.AddCommand(frameOffsetsCommand);

	assert(fileLoader.LoadFile(filePath));

	return animations;
}