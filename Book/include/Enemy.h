#pragma once

#include "SDLGameObject.h"

class Enemy : public SDLGameObject
{
public:
    Enemy(const LoaderParams& params);

    virtual void Update() override;
};