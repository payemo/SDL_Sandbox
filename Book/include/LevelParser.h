#pragma once

#include <vector>
#include "tinyxml2.h"

class Level;
struct Tileset;
class Layer;

class LevelParser
{
public:
    const Level& ParseLevel(const char* levelFile);

private:
    const Tileset& ParseTileset(tinyxml2::XMLElement& tilesetRoot);

    void ParseTileLayer(
        tinyxml2::XMLElement& tileElement,
        const std::vector<Layer*>& layers,
        const std::vector<Tileset>& tilesets);

private:
    int m_tileSize;
    int m_width;
    int m_height;
};