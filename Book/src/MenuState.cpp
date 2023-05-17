#include <iostream>
#include "MenuState.h"

const std::string MenuState::m_menuId = "MENU";

void MenuState::Update()
{

}

void MenuState::Render()
{

}

bool MenuState::OnEnter()
{
    std::cout << "Entering MenuState" << std::endl;
    return true;
}

bool MenuState::OnExit()
{
    std::cout << "Exiting MenuState" << std::endl;
    return true;

}