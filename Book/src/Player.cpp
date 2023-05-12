#include "Player.h"

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