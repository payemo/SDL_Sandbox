#pragma once

#include <vector>
#include "GameState.h"

class GameObject;

class PauseState : public GameState
{
public:
    virtual void Update();
    virtual void Render();

    virtual bool OnEnter();
    virtual bool OnExit();

    virtual const std::string& GetStateId() const;

private:
    static const std::string m_pauseId;

    std::vector<GameObject*> m_gameObjects;

private:
    static void m_pauseToMain();
    static void m_resumePlay();
};