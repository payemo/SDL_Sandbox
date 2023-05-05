#pragma once

#include "GameObject.h"

class SDLGameObject;

class SDLGameObject : public GameObject
{
public:
    SDLGameObject(const LoaderParams& params);

    virtual void Draw() override;
    virtual void Update() override;
    virtual void Clean() override;

protected:
    int m_x;
    int m_y;
    int m_w;
    int m_h;

    int m_currentRow{ 1 };
    int m_currentFrame{ 1 };

    std::string m_textureId;
};