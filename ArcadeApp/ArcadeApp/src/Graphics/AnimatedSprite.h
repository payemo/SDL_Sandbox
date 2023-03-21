#pragma once

#include "AnimationPlayer.h"
#include "Vec2D.h"
#include "Color.h"
#include <stdint.h>
#include <string>

class AARectangle;
class Screen;
class SpriteSheet;

class AnimatedSprite
{
public:
	AnimatedSprite();

	void Init(const std::string& animationPath, const SpriteSheet& spriteSheet, const Color& color = Color::White());
	void Update(uint32_t dt);
	void Draw(Screen& screen);

	void SetAnimation(const std::string& animationName, bool looped);
	Vec2D Size() const;

	void Stop();

	const AARectangle GetBoundingBox() const;

	inline Vec2D GetPosition() const { return mPosition; }
	inline void SetPosition(const Vec2D& pos) { mPosition = pos; }
	inline void MoveBy(const Vec2D& delta) { mPosition += delta; }
	inline bool IsFinished() const { return mAnimationPlayer.IsFinished(); }
	inline const Color& GetColor() const { return mColor; }
	const SpriteSheet* GetSpriteSheet() const { return mSpriteSheet; }

private:
	const SpriteSheet* mSpriteSheet{ nullptr };
	AnimationPlayer mAnimationPlayer;
	Vec2D mPosition{ Vec2D::Zero };
	Color mColor;
};