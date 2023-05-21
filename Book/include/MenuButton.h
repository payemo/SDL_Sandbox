#pragma once

#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class MenuButton : public SDLGameObject
{
public:
    MenuButton();

    virtual void Update() override;
    virtual void Load(const LoaderParams& params) override;

    inline void SetCallback(void(*callback)()) { m_callback = callback; }
    inline int GetCallbackId() const { return m_callbackId; }

private:
    enum ButtonState
    {
        MOUSE_OUT = 0,
        MOUSE_OVER = 1,
        CLICKED = 2
    };

    int m_callbackId{ 0 };
    void (*m_callback)();
    bool m_released{ false };
};

class MenuButtonCreator : public BaseCreator
{
    GameObject* Create() const
    {
        return new MenuButton();
    }
};