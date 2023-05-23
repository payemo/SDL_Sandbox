#pragma once

#include "MenuState.h"
#include "MenuButton.h"

void MenuState::SetCallbacks(const std::vector<Callback>& callbacks)
{
    for (auto gameObj : m_gameObjects) {
        MenuButton* menuButton = dynamic_cast<MenuButton*>(gameObj);
        if (menuButton) {
            menuButton->SetCallback(callbacks[menuButton->GetCallbackId()]);
        }
    }
}