#include "AnimatedGraphic.h"

AnimatedGraphic::AnimatedGraphic(const LoaderParams& params, int animationSpeed)
    : SDLGameObject(params), m_animationSpeed(animationSpeed)
{
}

void AnimatedGraphic::Update()
{
    m_currentFrame = int(((SDL_GetTicks() / (1000 / m_animationSpeed)) % 2));
}