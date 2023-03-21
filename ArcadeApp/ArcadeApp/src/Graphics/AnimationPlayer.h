#pragma once

#include "Animation.h"
#include <stdint.h>
#include <vector>
#include <string>

class AnimationPlayer
{
public:
	AnimationPlayer();

	bool Init(const std::string& animationsPath);
	bool Play(const std::string& animationName, bool looped);
	void Pause();
	void Stop();
	void Update(uint32_t dt);

	AnimationFrame GetCurrentAnimationFrame() const;

	inline bool IsFinished() const { return mIsFinished; }
	inline uint32_t GetCurrentFrameNumber() const { return mFrame; }


private:
	uint32_t mTime{ 0 };
	std::vector<Animation> mAnimations;
	size_t mCurrentAnimation{ 0 };
	uint32_t mFrame{ 0 };

	bool mLooped{ false };
	bool mIsPlaying{ false };
	bool mIsFinished{ false };
};