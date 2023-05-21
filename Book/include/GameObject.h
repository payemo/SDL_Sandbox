#pragma once

#include "SDL.h"
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"

class LoaderParams
{
public:
    LoaderParams(int x, int y, int w, int h, const std::string& textureId, int numFrames, int callbackId = 0, int animationSpeed = 0)
        : m_x(x),
        m_y(y),
        m_w(w),
        m_h(h),
        m_textureId(textureId),
        m_numFrames(numFrames),
        m_callbackId(callbackId),
        m_animationSpeed(animationSpeed)
    {
    }

    inline int GetX() const { return m_x; }
    inline int GetY() const { return m_y; }
    inline int GetWidth() const { return m_w; }
    inline int GetHeight() const { return m_h; }
    inline const std::string& GetTextureId() const { return m_textureId; }
    inline int GetNumFrames() const { return m_numFrames; }
    inline int GetCallbackId() const { return m_callbackId; }
    inline int GetAnimationSpeed() const { return m_animationSpeed; }

private:

    int m_x;
    int m_y;
    int m_w;
    int m_h;

    std::string m_textureId;

    int m_numFrames{ 1 };

    int m_callbackId;
    int m_animationSpeed;
};

class GameObject
{
public:
    virtual void Draw() = 0;
    virtual void Update() = 0;
    virtual void Clean() = 0;
    virtual void Load(const LoaderParams& params) = 0;

protected:
    GameObject() {}
    virtual ~GameObject() {}
};