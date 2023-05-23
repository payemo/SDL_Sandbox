#pragma once

#include <vector>
#include "GameState.h"

class GameStateMachine
{
public:
    void PushState(GameState* state);
    void ChangeState(GameState* state);
    void PopState();

    void Update();
    void Render();
    void Clean();

private:
    std::vector<GameState*> m_gameStates;
};