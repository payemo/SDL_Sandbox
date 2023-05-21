#pragma once

#include "MenuState.h"

class MainMenuState : public MenuState
{
public:
    virtual void Update() override;
    virtual void Render() override;

    virtual bool OnEnter() override;
    virtual bool OnExit() override;

    virtual const std::string& GetStateId() const override { return m_menuId; }

private:
    virtual void SetCallbacks(const std::vector<Callback>& callbacks) override;

    std::vector<GameObject*> m_gameObjects;

private:
    static const std::string m_menuId;

private: /// callback functions for menu items
    static void m_menuToPlay();
    static void m_exitFromMenu();
};