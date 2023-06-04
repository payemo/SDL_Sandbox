#pragma once

#include <vector>
#include "tinyxml2.h"

class Level;
struct Tileset;
class Layer;
class TileLayer;

class LevelParser
{
public:
    Level& ParseLevel(const char* levelFile);

private:
    const Tileset& ParseTileset(tinyxml2::XMLElement& tilesetRoot);

    TileLayer& ParseTileLayer(
        tinyxml2::XMLElement& tileElement,
        const std::vector<Tileset>& tilesets);

    void ParseTextures(tinyxml2::XMLElement& textureRoot);

    void ParseObjectLayer(tinyxml2::XMLElement& objectElement, std::vector<Layer*>& layers);

private:
    int m_tileSize;
    int m_width;
    int m_height;
};