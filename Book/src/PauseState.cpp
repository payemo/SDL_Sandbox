#include "PauseState.h"
#include "Game.h"
#include "MainMenuState.h"
#include "MenuButton.h"
#include "InputHandler.h"
#include "StateParser.h"

const std::string PauseState::m_pauseId = "PAUSE";

void PauseState::Update()
{
    for (auto obj : m_gameObjects) {
        obj->Update();
    }
}

void PauseState::Render()
{
    for (auto obj : m_gameObjects) {
        obj->Draw();
    }
}

bool PauseState::OnEnter()
{
    StateParser stateParser;
    stateParser.ParseState("assets/test.xml", m_pauseId, m_gameObjects, m_textureIdList);

    m_callbacks.push_back(nullptr);
    m_callbacks.push_back(m_pauseToMain);
    m_callbacks.push_back(m_resumePlay);

    MenuState::SetCallbacks(m_callbacks);

    std::cout << "Entering PauseState" << std::endl;
    return true;
}

bool PauseState::OnExit()
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

const std::string& PauseState::GetStateId() const
{
    return m_pauseId;
}

void PauseState::m_resumePlay()
{
    TheGame::Instance()->GetStateMachine().PopState();
}

void PauseState::m_pauseToMain()
{
    TheGame::Instance()->GetStateMachine().ChangeState(new MainMenuState());
}