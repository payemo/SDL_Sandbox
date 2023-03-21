#include "AnimationPlayer.h"

AnimationPlayer::AnimationPlayer()
{

}

bool AnimationPlayer::Init(const std::string& animationsPath)
{
	mAnimations = Animation::LoadAnimation(animationsPath);
	return mAnimations.size() > 0;
}

bool AnimationPlayer::Play(const std::string& animationName, bool looped)
{
	bool found = false;

	for (int i = 0; i < mAnimations.size(); ++i)
	{
		if (mAnimations[i].GetName() == animationName)
		{
			mCurrentAnimation = i;
			found = true;
			break;
		}
	}

	if (found)
	{
		mIsPlaying = true;
		mFrame = 0;
		mTime = 0;
		mLooped = looped;
		mIsFinished = false;
	}

	return found;
}

void AnimationPlayer::Pause()
{
	if (mIsFinished)
	{
		mIsPlaying = !mIsPlaying;
	}
}

void AnimationPlayer::Stop()
{
	mIsPlaying = false;
	mTime = 0;
	mFrame = 0;
	mIsFinished = true;
}

void AnimationPlayer::Update(uint32_t dt)
{
	if (mIsPlaying)
	{
		mTime += dt;

		int fps = mAnimations[mCurrentAnimation].FPS();

		float msPerFrame = static_cast<float>(1000) / static_cast<float>(fps);

		if (static_cast<float>(mTime) > msPerFrame)
		{
			mTime -= static_cast<uint32_t>(msPerFrame);

			if (mFrame + 1 < mAnimations[mCurrentAnimation].NumFrames())
			{
				++mFrame;
			}
			else if ((mFrame + 1 >= mAnimations[mCurrentAnimation].NumFrames()) && mLooped)
			{
				mFrame = 0;
			}
			else
			{
				mIsFinished = true;
			}
		}
	}
}

AnimationFrame AnimationPlayer::GetCurrentAnimationFrame() const
{
	if (mAnimations.empty())
	{
		return AnimationFrame();
	}

	uint32_t currentFrameNum = GetCurrentFrameNumber();
	return mAnimations[mCurrentAnimation].GetAnimationFrame(currentFrameNum);
}