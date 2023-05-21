#include <iostream>
#include "MainMenuState.h"
#include "Game.h"
#include "MenuButton.h"
#include "PlayerState.h"
#include "StateParser.h"

const std::string MainMenuState::m_menuId = "MENU";

void MainMenuState::Update()
{
    for (auto obj : m_gameObjects) {
        obj->Update();
    }
}

void MainMenuState::Render()
{
    for (auto obj : m_gameObjects) {
        obj->Draw();
    }
}

bool MainMenuState::OnEnter()
{
    // Parse state
    StateParser stateParser;
    stateParser.ParseState("assets/test.xml", m_menuId, m_gameObjects, m_textureIdList);

    m_callbacks.push_back(nullptr);
    m_callbacks.push_back(m_menuToPlay);
    m_callbacks.push_back(m_exitFromMenu);

    SetCallbacks(m_callbacks);

    std::cout << "Entering MenuState" << std::endl;
    return true;
}

bool MainMenuState::OnExit()
{
    for (auto gameObj : m_gameObjects) {
        gameObj->Clean();
    }
    m_gameObjects.clear();

    for (auto textureId : m_textureIdList) {
        TheTextureManager::Instance()->ClearFromTextureMap(textureId);
    }

    std::cout << "Exiting MenuState" << std::endl;
    return true;

}

void MainMenuState::m_menuToPlay()
{
    TheGame::Instance()->GetStateMachine().ChangeState(new PlayerState());
}

void MainMenuState::m_exitFromMenu()
{
    TheGame::Instance()->Quit();
}

void MainMenuState::SetCallbacks(const std::vector<Callback>& callbacks)
{
    for (auto gameObj : m_gameObjects) {
        MenuButton* menuButton = dynamic_cast<MenuButton*>(gameObj);
        if (menuButton) {
            menuButton->SetCallback(callbacks[menuButton->GetCallbackId()]);
        }
    }
}