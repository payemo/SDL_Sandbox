#include "SDLGameObject.h"
#include "Game.h"

SDLGameObject::SDLGameObject(const LoaderParams& params)
    : GameObject(params)
{
    m_x = params.GetX();
    m_y = params.GetY();
    m_w = params.GetWidth();
    m_h = params.GetHeight();

    m_textureId = params.GetTextureId();
}

void SDLGameObject::Draw()
{
    TextureManager::Instance()->DrawFrame(
        m_textureId,
        m_x,
        m_y,
        m_w,
        m_h,
        m_currentRow,
        m_currentFrame,
        TheGame::Instance()->GetRenderer());
}

void SDLGameObject::Update()
{

}

void SDLGameObject::Clean()
{

}