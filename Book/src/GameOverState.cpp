#include "GameOverState.h"
#include "Game.h"
#include "MainMenuState.h"
#include "PlayerState.h"
#include "AnimatedGraphic.h"
#include "MenuButton.h"
#include "InputHandler.h"
#include "StateParser.h"

const std::string GameOverState::m_gameOverId = "GAMEOVER";

void GameOverState::Update()
{
    for (auto obj : m_gameObjects) {
        obj->Update();
    }
}

void GameOverState::Render()
{
    for (auto obj : m_gameObjects) {
        obj->Draw();
    }
}

bool GameOverState::OnEnter()
{
    StateParser stateParser;
    stateParser.ParseState("assets/test.xml", m_gameOverId, m_gameObjects, m_textureIdList);

    m_callbacks.push_back(nullptr);
    m_callbacks.push_back(m_gameOverToMain);
    m_callbacks.push_back(m_restartPlay);

    MenuState::SetCallbacks(m_callbacks);

    std::cout << "Entering PauseState" << std::endl;
    return true;
}

bool GameOverState::OnExit()
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

    std::cout << "Exiting PauseState" << std::endl;
    return true;
}

const std::string& GameOverState::GetStateId() const
{
    return m_gameOverId;
}

void GameOverState::m_gameOverToMain()
{
    TheGame::Instance()->GetStateMachine().ChangeState(new MainMenuState());
}

void GameOverState::m_restartPlay()
{
    TheGame::Instance()->GetStateMachine().ChangeState(new PlayerState());
}