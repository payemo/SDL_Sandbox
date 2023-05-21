#include "GameOverState.h"
#include "Game.h"
#include "MenuState.h"
#include "PlayerState.h"
#include "AnimatedGraphic.h"
#include "MenuButton.h"
#include "InputHandler.h"

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
    if (!TheTextureManager::Instance()->Load("assets/gameover.png", "gameovertext", TheGame::Instance()->GetRenderer())) {
        return false;
    }

    if (!TheTextureManager::Instance()->Load("assets/main.png", "mainbutton", TheGame::Instance()->GetRenderer())) {
        return false;
    }

    if (!TheTextureManager::Instance()->Load("assets/restart.png", "mainbutton", TheGame::Instance()->GetRenderer())) {
        return false;
    }

    GameObject* gameOverText = new AnimatedGraphic;
    gameOverText->Load(*(new LoaderParams(200, 100, 190, 30, "gameovertext", 1, 0, 2)));

    GameObject* mainButton = new MenuButton(m_gameOverToMain);
    mainButton->Load(*(new LoaderParams(200, 200, 200, 80, "mainbutton", 1)));

    GameObject* restartButton = new MenuButton(m_restartPlay);
    restartButton->Load(*(new LoaderParams(200, 300, 200, 80, "restartbutton", 1)));

    m_gameObjects.push_back(gameOverText);
    m_gameObjects.push_back(mainButton);
    m_gameObjects.push_back(restartButton);

    std::cout << "Entering PauseState" << std::endl;
    return true;
}

bool GameOverState::OnExit()
{
    for (auto obj : m_gameObjects) {
        obj->Clean();
    }
    m_gameObjects.clear();

    TheTextureManager::Instance()->ClearFromTextureMap("gameovertext");
    TheTextureManager::Instance()->ClearFromTextureMap("mainbutton");
    TheTextureManager::Instance()->ClearFromTextureMap("restartbutton");

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
    TheGame::Instance()->GetStateMachine().ChangeState(new MenuState());
}

void GameOverState::m_restartPlay()
{
    TheGame::Instance()->GetStateMachine().ChangeState(new PlayerState());
}