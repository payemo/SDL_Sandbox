#include "MenuButton.h"
#include "InputHandler.h"
#include "GameObject.h"

MenuButton::MenuButton(const LoaderParams& params, void (*callback)())
    : SDLGameObject(params), m_callback(callback)
{
    m_currentFrame = MOUSE_OUT;
}

void MenuButton::Update()
{
    Vector2D mousePos = TheInputHandler::Instance()->GetMousePosition();

    if (mousePos.GetX() < (m_position.GetX() + m_w) &&
        mousePos.GetX() > m_position.GetX() &&
        mousePos.GetY() < (m_position.GetY() + m_h) &&
        mousePos.GetY() > m_position.GetY()) {

        if (TheInputHandler::Instance()->GetMouseButtonState(LEFT) && m_released) {
            m_currentFrame = CLICKED;

            m_callback();
            m_released = false;
        }
        else if (!TheInputHandler::Instance()->GetMouseButtonState(LEFT)) {
            m_released = true;
            m_currentFrame = MOUSE_OVER;
        }
    }
    else {
        m_currentFrame = MOUSE_OUT;
    }
}