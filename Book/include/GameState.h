#pragma once

#include <string>
#include <vector>
#include "GameObject.h"

class GameState
{
public:
    virtual void Update() = 0;
    virtual void Render() = 0;

    virtual bool OnEnter() = 0;
    virtual bool OnExit() = 0;

    virtual const std::string& GetStateId() const = 0;

protected:
    std::vector<GameObject*> m_gameObjects;
    std::vector<std::string> m_textureIdList;
};