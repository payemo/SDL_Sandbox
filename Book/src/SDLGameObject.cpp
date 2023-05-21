#include "SDLGameObject.h"
#include "Game.h"

SDLGameObject::SDLGameObject() : GameObject()
{
}

void SDLGameObject::Load(const LoaderParams& params)
{
    m_position = Vector2D(params.GetX(), params.GetY());;
    m_velocity = Vector2D(0, 0);
    m_acceleration = Vector2D(0, 0);
    m_w = params.GetWidth();
    m_h = params.GetHeight();

    m_textureId = params.GetTextureId();
    m_numFrames = params.GetNumFrames();
}

void SDLGameObject::Draw()
{
    if (m_velocity.GetX() > 0) {
        TextureManager::Instance()->DrawFrame(
        m_textureId,
        static_cast<Uint32>(m_position.GetX()),
        static_cast<Uint32>(m_position.GetY()),
        m_w,
        m_h,
        m_currentRow,
        m_currentFrame,
        TheGame::Instance()->GetRenderer(),
        SDL_FLIP_HORIZONTAL);
    }
    else {
        TextureManager::Instance()->DrawFrame(
        m_textureId,
        static_cast<Uint32>(m_position.GetX()),
        static_cast<Uint32>(m_position.GetY()),
        m_w,
        m_h,
        m_currentRow,
        m_currentFrame,
        TheGame::Instance()->GetRenderer());
    }
    
}

void SDLGameObject::Update()
{
    m_velocity += m_acceleration;
    m_position += m_velocity;
}

void SDLGameObject::Clean()
{

}