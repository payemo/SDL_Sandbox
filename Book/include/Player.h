#pragma once

#include "SDLGameObject.h"

class Player : public SDLGameObject
{
public:
    Player();

    virtual void Update() override;

private:
    void HandleInput();
};