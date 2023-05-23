#pragma once

#include <vector>
#include "MenuState.h"

class GameObject;

class PauseState : public MenuState
{
public:
    virtual void Update();
    virtual void Render();

    virtual bool OnEnter();
    virtual bool OnExit();

    virtual const std::string& GetStateId() const;

private:
    static const std::string m_pauseId;

    static void m_pauseToMain();
    static void m_resumePlay();
};