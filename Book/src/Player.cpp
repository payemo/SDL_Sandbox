#include "Player.h"
#include "InputHandler.h"

Player::Player(const LoaderParams& params)
    : SDLGameObject(params)
{
}

void Player::Update()
{
    m_currentFrame = int(((SDL_GetTicks() / 100) % 6));

    //m_acceleration.SetX(1);
    m_velocity.SetX(1);

    SDLGameObject::Update();
}

void Player::HandleInput()
{
    InputHandler* ih = TheInputHandler::Instance();

    if (ih->XValue(0, 1) > 0 || ih->XValue(0, 1) < 0) {
        m_velocity.SetX(ih->XValue(0, 1));
    }

    if (ih->YValue(0, 1) > 0 || ih->YValue(0, 1) < 0) {
        m_velocity.SetY(ih->YValue(0, 1));
    }
}