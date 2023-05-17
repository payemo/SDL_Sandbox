#pragma once

#include <vector>
#include "GameState.h"

class GameStateMachine
{
public:
    void PushState(GameState* state);
    void ChangeState(GameState* state);
    void PopState();

private:
    std::vector<GameState*> m_gameStates;
};