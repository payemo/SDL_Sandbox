#pragma once

#include <vector>
#include "GameState.h"
#include "GameObject.h"

class MenuState : public GameState
{
protected:
    typedef void(*Callback)();

    void SetCallbacks(const std::vector<Callback>& callbacks);

    std::vector<Callback> m_callbacks;
};