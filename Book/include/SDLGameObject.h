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

    inline const Vector2D& GetPosition() const { return m_position; }
    inline int GetWidth() const { return m_w; }
    inline int GetHeight() const { return m_h; }

protected:
    Vector2D m_position;
    Vector2D m_velocity;
    Vector2D m_acceleration;
    int m_w;
    int m_h;

    int m_currentRow{ 1 };
    int m_currentFrame{ 1 };
    int m_numFrames{ 0 };

    std::string m_textureId;
};