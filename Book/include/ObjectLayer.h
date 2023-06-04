#pragma once

#include "Layer.h"
#include <vector>

class GameObject;

class ObjectLayer : public Layer
{
public:
    virtual ~ObjectLayer() {}

    virtual void Update() override;
    virtual void Render() override;

    inline std::vector<GameObject*>& GetGameObjects() { return m_gameObjects; }

private:
    std::vector<GameObject*> m_gameObjects;
};