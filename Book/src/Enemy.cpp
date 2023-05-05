#include "Enemy.h"

Enemy::Enemy(const LoaderParams& params)
    : SDLGameObject(params)
{
}

void Enemy::Update()
{
    m_x += 1;
    m_y += 1;
    m_currentFrame = int(((SDL_GetTicks() / 100) % 6));
}