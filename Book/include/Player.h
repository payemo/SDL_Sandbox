#pragma once

#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class Player : public SDLGameObject
{
public:
    Player();

    virtual void Update() override;

private:
    void HandleInput();
};

class PlayerCreator : public BaseCreator
{
    GameObject* Create() const
    {
        return new Player();
    }
};