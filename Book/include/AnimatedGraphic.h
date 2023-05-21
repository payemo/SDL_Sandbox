#pragma once

#include "SDLGameObject.h"

class AnimatedGraphic : public SDLGameObject
{
public:
    AnimatedGraphic();

    virtual void Update() override;
    virtual void Load(const LoaderParams& params) override;

private:
    int m_animationSpeed{ 0 };
};