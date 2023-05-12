#include "SDLGameObject.h"
#include "Game.h"

SDLGameObject::SDLGameObject(const LoaderParams& params)
    : GameObject(params), 
    m_position(params.GetX(), params.GetY()),
    m_velocity(0, 0), m_acceleration(0, 0)
{
    m_w = params.GetWidth();
    m_h = params.GetHeight();

    m_textureId = params.GetTextureId();
}

void SDLGameObject::Draw()
{
    TextureManager::Instance()->DrawFrame(
        m_textureId,
        static_cast<int>(m_position.GetX()),
        static_cast<int>(m_position.GetY()),
        m_w,
        m_h,
        m_currentRow,
        m_currentFrame,
        TheGame::Instance()->GetRenderer());
}

void SDLGameObject::Update()
{
    m_velocity += m_acceleration;
    m_position += m_velocity;
}

void SDLGameObject::Clean()
{

}