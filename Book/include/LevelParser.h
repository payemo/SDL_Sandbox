#pragma once

#include <vector>
#include "tinyxml2.h"
#include "Level.h"

class LevelParser
{
public:
    const Level& ParseLevel(const char* levelFile);

private:
    void ParseTilesets(
        tinyxml2::XMLElement& tilesetRoot,
        const std::vector<Tileset>& tilesets);

    void ParseTileLayer(
        tinyxml2::XMLElement& tileElement,
        const std::vector<Layer*> layers,
        const std::vector<Tileset>& tilesets);

private:
    int m_tileSize;
    int m_width;
    int m_height;
};