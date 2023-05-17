#include <iostream>
#include "PlayerState.h"

const std::string PlayerState::m_playId = "PLAY";

void PlayerState::Update()
{

}

void PlayerState::Render()
{

}

bool PlayerState::OnEnter()
{
    std::cout << "Entering MenuState" << std::endl;
    return true;
}

bool PlayerState::OnExit()
{
    std::cout << "Exiting MenuState" << std::endl;
    return true;
}