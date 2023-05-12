#pragma once

#include "GameObject.h"
#include "Vector2D.h"

class SDLGameObject;

class SDLGameObject : public GameObject
{
public:
    SDLGameObject(const LoaderParams& params);

    virtual void Draw() override;
    virtual void Update() override;
    virtual void Clean() override;

protected:
    Vector2D m_position;
    Vector2D m_velocity;
    Vector2D m_acceleration;
    int m_w;
    int m_h;

    int m_currentRow{ 1 };
    int m_currentFrame{ 1 };

    std::string m_textureId;
};