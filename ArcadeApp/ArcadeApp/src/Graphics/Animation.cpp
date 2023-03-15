#include "Animation.h"
#include "FileCommandLoader.h"

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
}