#include "Level.h"
#include "Layer.h"

Level::Level() {}

void Level::Update()
{
    for (auto layer : m_layers) {
        layer->Update();
    }
}

void Level::Render()
{
    for (auto layer : m_layers) {
        layer->Render();
    }
}