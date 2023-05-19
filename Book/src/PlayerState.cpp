#include <iostream>
#include "PlayerState.h"
#include "GameObject.h"
#include "Game.h"
#include "Player.h"

const std::string PlayerState::m_playId = "PLAY";

void PlayerState::Update()
{
    for (auto gameObj : m_gameObjects) {
        gameObj->Update();
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

    GameObject* player = new Player(
        *(new LoaderParams(100, 100, 128, 55, "helicopter")));

    m_gameObjects.push_back(player);

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

    std::cout << "Exiting PlayState" << std::endl;
    return true;
}