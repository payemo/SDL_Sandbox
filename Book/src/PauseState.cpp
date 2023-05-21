#include "PauseState.h"
#include "Game.h"
#include "MainMenuState.h"
#include "MenuButton.h"
#include "InputHandler.h"

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
    if (!TheTextureManager::Instance()->Load("assets/resume.png", "resumebutton", TheGame::Instance()->GetRenderer())) {
        return false;
    }

    if (!TheTextureManager::Instance()->Load("assets/main.png", "mainbutton", TheGame::Instance()->GetRenderer())) {
        return false;
    }

    GameObject* resumeButton = new MenuButton();
    resumeButton->Load(*(new LoaderParams(200, 100, 200, 80, "resumebutton", 0)));

    GameObject* mainButton = new MenuButton();
    mainButton->Load(*(new LoaderParams(200, 300, 200, 80, "mainbutton", 0)));

    m_gameObjects.push_back(resumeButton);
    m_gameObjects.push_back(mainButton);

    std::cout << "Entering PauseState" << std::endl;
    return true;
}

bool PauseState::OnExit()
{
    for (auto obj : m_gameObjects) {
        obj->Clean();
    }
    m_gameObjects.clear();

    TheTextureManager::Instance()->ClearFromTextureMap("resumebutton");
    TheTextureManager::Instance()->ClearFromTextureMap("mainbutton");

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