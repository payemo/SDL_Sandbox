#pragma once

#include "SDLGameObject.h"

class MenuButton : public SDLGameObject
{
public:
    MenuButton(const LoaderParams& params, void (*callback)());

    virtual void Update() override;

private:
    enum ButtonState
    {
        MOUSE_OUT = 0,
        MOUSE_OVER = 1,
        CLICKED = 2
    };

    void (*m_callback)();
    bool m_released{ false };
};