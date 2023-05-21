#pragma once

#include "SDLGameObject.h"

class Enemy : public SDLGameObject
{
public:
    Enemy();

    virtual void Update() override;
    virtual void Load(const LoaderParams& params) override;
};