#pragma once

#include <vector>
#include <string>

class Layer;

struct Tileset
{
    int firstGridId;
    int tileWidth;
    int tileHeight;
    int specing;
    int margin;
    int width;
    int height;
    int numColumns;
    std::string name;
};

class Level
{
public:
    Level();
    ~Level() {}

    void Update();
    void Render();

    inline const std::vector<Tileset>& GetTilesets() { return m_tilesets; }
    inline const std::vector<Layer*>& GetLayers() { return m_layers; }

private:
    std::vector<Tileset> m_tilesets;
    std::vector<Layer*> m_layers;
};