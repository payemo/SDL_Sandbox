#include "Enemy.h"

Enemy::Enemy(const LoaderParams& params)
    : SDLGameObject(params)
{
    m_velocity.SetY(2);
    m_velocity.SetX(0.001);
}

void Enemy::Update()
{

    m_currentFrame = int(((SDL_GetTicks() / 100) % 5));

    if (m_position.GetY() < 0) {
        m_velocity.SetY(2);
    }
    else if (m_position.GetY() > 400) {
        m_velocity.SetY(-2);
    }

    SDLGameObject::Update();

    /*m_position.SetX(m_position.GetX() + 1);
    m_position.SetY(m_position.GetY() + 1);
    m_currentFrame = int(((SDL_GetTicks() / 100) % 6));*/
}