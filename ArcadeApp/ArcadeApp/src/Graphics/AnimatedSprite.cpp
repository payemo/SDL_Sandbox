#include "AnimatedSprite.h"
#include "AARectangle.h"
#include "Screen.h"

AnimatedSprite::AnimatedSprite()
{

}

void AnimatedSprite::Init(const std::string& animationPath, const SpriteSheet& spriteSheet, const Color& color)
{
	mAnimationPlayer.Init(animationPath);
	mSpriteSheet = &spriteSheet;
	mColor = Color::Cyan();
}

void AnimatedSprite::Update(uint32_t dt)
{
	mAnimationPlayer.Update(dt);
}

void AnimatedSprite::Draw(Screen& screen)
{
	AnimationFrame frame = mAnimationPlayer.GetCurrentAnimationFrame();

	Color frameColor = frame.frameColor;

	if (!frame.frameColorSet)
	{
		frameColor = mColor;
	}

	screen.Draw(*mSpriteSheet, frame.frame, mPosition + frame.offset, frameColor);

	if (frame.overlay.size() > 0)
	{
		screen.Draw(*mSpriteSheet, frame.overlay, mPosition, frame.overlayColor);
	}
}

void AnimatedSprite::SetAnimation(const std::string& animationName, bool looped)
{
	mAnimationPlayer.Play(animationName, looped);
}

Vec2D AnimatedSprite::Size() const
{
	return mAnimationPlayer.GetCurrentAnimationFrame().size;
}

void AnimatedSprite::Stop()
{
	mAnimationPlayer.Stop();
}

const AARectangle AnimatedSprite::GetBoundingBox() const
{
	AARectangle box = { mPosition, static_cast<uint32_t>(Size().GetX()), static_cast<uint32_t>(Size().GetY()) };
	return box;
}