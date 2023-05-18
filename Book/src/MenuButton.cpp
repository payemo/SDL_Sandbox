#include "MenuButton.h"
#include "InputHandler.h"
#include "GameObject.h"

MenuButton::MenuButton(const LoaderParams& params)
    : SDLGameObject(params)
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

        m_currentFrame = MOUSE_OVER;

        if (TheInputHandler::Instance()->GetMouseButtonState(LEFT)) {
            m_currentFrame = CLICKED;
        }
    }
    else {
        m_currentFrame = MOUSE_OUT;
    }
}