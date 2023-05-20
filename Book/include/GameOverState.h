#pragma once

#include <vector>
#include "GameState.h"

class GameObject;

class GameOverState : public GameState
{
public:
    virtual void Update() override;
    virtual void Render() override;

    virtual bool OnEnter() override;
    virtual bool OnExit() override;

    virtual const std::string& GetStateId() const override;

private:
    static void m_gameOverToMain();
    static void m_restartPlay();

    static const std::string m_gameOverId;

    std::vector<GameObject*> m_gameObjects;
};