#include "Enemy.h"

Enemy::Enemy(const LoaderParams& params)
    : SDLGameObject(params)
{
}

void Enemy::Update()
{
    m_position.SetX(m_position.GetX() + 1);
    m_position.SetY(m_position.GetY() + 1);
    m_currentFrame = int(((SDL_GetTicks() / 100) % 6));
}