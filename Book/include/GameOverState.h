#pragma once

#include <vector>
#include "MenuState.h"

class GameOverState : public MenuState
{
public:
    virtual void Update() override;
    virtual void Render() override;

    virtual bool OnEnter() override;
    virtual bool OnExit() override;

    virtual const std::string& GetStateId() const override;

private:
    static const std::string m_gameOverId;

    static void m_gameOverToMain();
    static void m_restartPlay();
};