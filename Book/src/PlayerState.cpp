#include <iostream>
#include "PlayerState.h"
#include "GameObject.h"
#include "Game.h"
#include "Player.h"
#include "InputHandler.h"
#include "PauseState.h"
#include "Enemy.h"
#include "GameOverState.h"
#include "SDLGameObject.h"
#include "PlayerCreator.h"

const std::string PlayerState::m_playId = "PLAY";

void PlayerState::Update()
{
    if (TheInputHandler::Instance()->isKeyPressed(SDL_SCANCODE_ESCAPE)) {
        TheGame::Instance()->GetStateMachine().PushState(new PauseState());
    }

    for (auto gameObj : m_gameObjects) {
        gameObj->Update();
    }

    SDLGameObject* obj1 = dynamic_cast<SDLGameObject*>(m_gameObjects[0]);
    SDLGameObject* obj2 = dynamic_cast<SDLGameObject*>(m_gameObjects[1]);
    if (CheckCollision(*obj1, *obj2)) {
        TheGame::Instance()->GetStateMachine().PushState(new GameOverState());
    }
}

void PlayerState::Render()
{
    for (auto gameObj : m_gameObjects) {
        gameObj->Draw();
    }
}

bool PlayerState::OnEnter()
{
    if (!TheTextureManager::Instance()->Load("assets/helicopter.png", "helicopter", TheGame::Instance()->GetRenderer())) {
        return false;
    }

    if (!TheTextureManager::Instance()->Load("assets/helicopter2.png", "helicopter2", TheGame::Instance()->GetRenderer())) {
        return false;
    }

    GameObject* player = new Player;
    player->Load(*(new LoaderParams(500, 100, 128, 55, "helicopter", 5)));

    GameObject* enemy = new Enemy;
    enemy->Load(*(new LoaderParams(100, 100, 128, 55, "helicopter2", 5)));

    m_gameObjects.push_back(player);
    m_gameObjects.push_back(enemy);

    std::cout << "Entering PlayState" << std::endl;
    return true;
}

bool PlayerState::OnExit()
{
    for (auto gameObj : m_gameObjects) {
        gameObj->Clean();
    }
    m_gameObjects.clear();

    TheTextureManager::Instance()->ClearFromTextureMap("helicopter");
    TheTextureManager::Instance()->ClearFromTextureMap("helicopter2");

    std::cout << "Exiting PlayState" << std::endl;
    return true;
}

bool PlayerState::CheckCollision(const SDLGameObject& obj1, const SDLGameObject& obj2)
{
    int x_a = obj1.GetPosition().GetX();
    int y_a = obj1.GetPosition().GetY();

    int x_b = obj2.GetPosition().GetX();
    int y_b = obj2.GetPosition().GetY();

    if ((x_a < (x_b + obj2.GetWidth()) && (x_a + obj1.GetWidth() > x_b) &&
        (y_a < (y_b + obj2.GetHeight()) && (y_a + obj1.GetHeight() > y_b)))) {
        return true;
    }

    return false;
}