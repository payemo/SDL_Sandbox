#include "GameObject.h"
#include "ObjectLayer.h"

void ObjectLayer::Update()
{
    for (auto& gameObj : m_gameObjects) {
        gameObj->Update();
    }
}

void ObjectLayer::Render()
{
    for (auto& gameObj : m_gameObjects) {
        gameObj->Draw();
    }
}