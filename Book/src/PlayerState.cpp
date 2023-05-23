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
#include "StateParser.h"

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
    StateParser stateParser;
    stateParser.ParseState("assets/test.xml", m_playId, m_gameObjects, m_textureIdList);

    std::cout << "Entering PlayState" << std::endl;
    return true;
}

bool PlayerState::OnExit()
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