#pragma once

#include "Excluder.h"
#include "Color.h"

class Ball;
class Screen;
struct BoundaryEdge;
class AARectangle;

class Block : public Excluder
{
public:
	static const int UNBREAKABLE = -1;

	Block();

	void Init(const AARectangle& rect, int hp, const Color& outlineColor, const Color& fillColor);
	void Draw(Screen& screen);
	void Bounce(Ball& ball, const BoundaryEdge& edge);

	void ReduceHP();
	inline int GetHP() const { return mHp; }
	inline bool IsDestroyed() const { return mHp == 0; }
	inline const Color& GetOutlineColor() const { return mOutlineColor; }
	inline const Color& GetFillColor() const { return mFillColor; }

private:
	Color mOutlineColor{Color::White()};
	Color mFillColor{Color::White()};

	int mHp{1}; // -1 for unbreakable
};