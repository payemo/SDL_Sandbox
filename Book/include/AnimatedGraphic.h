#pragma once

#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class AnimatedGraphic : public SDLGameObject
{
public:
    AnimatedGraphic();

    virtual void Update() override;
    virtual void Load(const LoaderParams& params) override;

private:
    int m_animationSpeed{ 0 };
};

class AnimatedGraphicCreator : public BaseCreator
{
    GameObject* Create() const
    {
        return new AnimatedGraphic();
    }
};