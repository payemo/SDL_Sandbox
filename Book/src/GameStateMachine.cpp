#include "GameStateMachine.h"

void GameStateMachine::PushState(GameState* state)
{
    m_gameStates.push_back(state);
    m_gameStates.back()->OnEnter();
}

void GameStateMachine::ChangeState(GameState* state)
{
    if (!m_gameStates.empty()) {
        if (m_gameStates.back()->GetStateId() == state->GetStateId()) {
            return;
        }
        if (m_gameStates.back()->OnExit()) {
            delete m_gameStates.back();
            m_gameStates.pop_back();
        }
    }

    // push a new state
    m_gameStates.push_back(state);
    m_gameStates.back()->OnEnter();
}

void GameStateMachine::PopState()
{
    if (!m_gameStates.empty()) {
        if (m_gameStates.back()->OnExit()) {
            delete m_gameStates.back();
            m_gameStates.pop_back();
        }
    }
}