#pragma once

#include "SDLGameObject.h"

class AnimatedGraphic : public SDLGameObject
{
public:
    AnimatedGraphic(const LoaderParams& params, int animationSpeed);

    virtual void Update() override;

private:
    int m_animationSpeed;
};