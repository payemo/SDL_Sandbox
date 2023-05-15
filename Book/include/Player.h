#pragma once

#include "SDLGameObject.h"

class Player : public SDLGameObject
{
public:
    Player(const LoaderParams& params);

    virtual void Update() override;

private:
    void HandleInput();
};