#pragma once

#include <vector>
#include <string>
#include "LevelParser.h"

class Layer;

struct Tileset
{
    int firstGridId;
    int tileWidth;
    int tileHeight;
    int spacing;
    int margin;
    int width;
    int height;
    int numColumns;
    std::string name;
};

class Level
{
public:
    ~Level() {}

    void Update();
    void Render();

    inline const std::vector<Tileset>& GetTilesets() { return m_tilesets; }
    inline void AddTileset(const Tileset& tileset) { m_tilesets.push_back(tileset); }

    inline std::vector<Layer*>& GetLayers() { return m_layers; }
    inline void AddLayer(Layer* layer) { m_layers.push_back(layer); }

private:
    friend class LevelParser;
    Level();

private:
    std::vector<Tileset> m_tilesets;
    std::vector<Layer*> m_layers;
};