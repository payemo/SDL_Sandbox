#pragma once

#include "AnimatedSprite.h"
#include "Vec2D.h"
#include "PacmanGameUtils.h"
#include "AARectangle.h"
#include "Color.h"
#include <string>
#include <stdint.h>

class Screen;
class SpriteSheet;

class Actor
{
public:
	virtual ~Actor() {}
	virtual void Init(
		const SpriteSheet& spriteSheet, 
		const std::string& animationPath, 
		const Vec2D& initialPos, 
		uint32_t movementSpeed, 
		bool updateSpriteOnMovement, 
		const Color& spriteColor = Color::White());

	virtual void Update(uint32_t dt);
	virtual void Draw(Screen& screen);

	virtual void Stop();


	AARectangle GetEatingBoundingBox() const;

	inline bool IsFinishedAnimation() const { return mSprite.IsFinished(); }
	inline const AARectangle GetBoundingBox() const { return mSprite.GetBoundingBox(); }
	inline void MoveBy(const Vec2D& delta) { mSprite.MoveBy(delta); }
	inline void MoveTo(const Vec2D& position) { mSprite.SetPosition(position); }
	inline Vec2D Position() const { return mSprite.GetPosition(); }
	inline PacmanMovement GetMovementDirection() const { return mMovementDirection; }

	virtual inline void SetMovementDirection(PacmanMovement direction) { mMovementDirection = direction; }
	inline const Color& GetSpriteColor() const { return mSprite.GetColor(); }
protected:
	void SetAnimation(const std::string& animationName, bool looped);

	inline void ResetDelta() { mDelta = Vec2D::Zero; }
	inline void SetMovementSpeed(uint32_t movementSpeed) { mMovementSpeed = movementSpeed; }

	AnimatedSprite mSprite;

private:
	Vec2D mDelta;
	PacmanMovement mMovementDirection;
	uint32_t mMovementSpeed;
	bool mUpdateSpriteOnUpdate;
};