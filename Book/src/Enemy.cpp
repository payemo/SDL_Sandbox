#include "Enemy.h"

Enemy::Enemy(): SDLGameObject()
{
}

void Enemy::Load(const LoaderParams& params)
{
    SDLGameObject::Load(params);
    m_velocity.SetY(2);
    m_velocity.SetX(0.001);
}

void Enemy::Update()
{

    m_currentFrame = int(((SDL_GetTicks() / 100) % m_numFrames));

    if (m_position.GetY() < 0) {
        m_velocity.SetY(2);
    }
    else if (m_position.GetY() > 400) {
        m_velocity.SetY(-2);
    }

    SDLGameObject::Update();
}