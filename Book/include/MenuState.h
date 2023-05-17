#pragma once

#include "GameState.h"

class MenuState : public GameState
{
public:
    virtual void Update() override;
    virtual void Render() override;

    virtual bool OnEnter() override;
    virtual bool OnExit() override;

    virtual const std::string& GetStateId() const override { return m_menuId; }

private:
    static const std::string m_menuId;
};