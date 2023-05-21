#include "AnimatedGraphic.h"

AnimatedGraphic::AnimatedGraphic() : SDLGameObject()
{
}

void AnimatedGraphic::Load(const LoaderParams& params)
{
    SDLGameObject::Load(params);
    m_animationSpeed = params.GetAnimationSpeed();
}

void AnimatedGraphic::Update()
{
    m_currentFrame = int(((SDL_GetTicks() / (1000 / m_animationSpeed)) % m_numFrames));
}