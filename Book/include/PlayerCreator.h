#pragma once

#include "GameObjectFactory.h"
#include "Player.h"

class PlayerCreator : public BaseCreator
{
    GameObject* Create() const
    {
        return new Player();
    }
};