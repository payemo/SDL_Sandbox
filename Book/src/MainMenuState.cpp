#include <iostream>
#include "MainMenuState.h"
#include "Game.h"
#include "MenuButton.h"
#include "PlayerState.h"
#include "StateParser.h"
#include "InputHandler.h"

const std::string MainMenuState::m_menuId = "MENU";

void MainMenuState::Update()
{
    for (auto obj : m_gameObjects) {
        if (obj) {
            obj->Update();
        }
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

    MenuState::SetCallbacks(m_callbacks);

    std::cout << "Entering MenuState" << std::endl;
    return true;
}

bool MainMenuState::OnExit()
{
    if (!m_gameObjects.empty()) {
        for (auto gameObj : m_gameObjects) {
            gameObj->Clean();
        }
        m_gameObjects.clear();
    }

    for (auto textureId : m_textureIdList) {
        TheTextureManager::Instance()->ClearFromTextureMap(textureId);
    }

    TheInputHandler::Instance()->Reset();

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