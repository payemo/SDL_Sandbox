#include "BreakOut.h"
#include <iostream>

void BreakOut::Init(GameController& gameController)
{
	std::cout << "Break Out Game Init()" << std::endl;
}

void BreakOut::Update(uint32_t dt)
{
	std::cout << "Break Out Game Update()" << std::endl;
}

void BreakOut::Draw(Screen& screen)
{
	std::cout << "Break Out Game Draw()" << std::endl;
}

const std::string& BreakOut::GetName() const
{
	return "Break Out";
}