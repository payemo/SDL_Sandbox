#pragma once

#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class Enemy : public SDLGameObject
{
public:
    Enemy();

    virtual void Update() override;
    virtual void Load(const LoaderParams& params) override;
};

class EnemyCreator : public BaseCreator
{
    GameObject* Create() const
    {
        return new Enemy();
    }
};