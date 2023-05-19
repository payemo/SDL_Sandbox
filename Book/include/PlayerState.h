#pragma once

#include <vector>
#include "GameState.h"

class GameObject;

class PlayerState : public GameState
{
public:
    virtual void Update() override;
    virtual void Render() override;

    virtual bool OnEnter() override;
    virtual bool OnExit() override;

    virtual const std::string& GetStateId() const override { return m_playId; }

private:
    static const std::string m_playId;

    std::vector<GameObject*> m_gameObjects;
};