#include "LevelParser.h"

const Level& LevelParser::ParseLevel(const char* levelFile)
{
    tinyxml2::XMLDocument levelDocument;
    levelDocument.LoadFile(levelFile);

    // Create level object
    Level* level = new Level;

    tinyxml2::XMLElement* root = levelDocument.RootElement();

    m_tileSize = root->IntAttribute("tilewidth");
    m_width = root->IntAttribute("width");
    m_height = root->IntAttribute("height");

    // Parse the tilesets
    {
        tinyxml2::XMLElement* child = root->FirstChildElement();
        while (child != nullptr) {
            if (child->Value() == "tileset") {
                ParseTilesets(*child, level->GetTilesets());
            }
            child = child->NextSiblingElement();
        }
    }

    // Parse anyy object layer
    {
        tinyxml2::XMLElement* child = root->FirstChildElement();
        while (child != nullptr) {
            if (child->Value() == "tileset") {
                ParseTileLayer(*child, level->GetLayers(), level->GetTilesets());
            }
        }
    }
}

void LevelParser::ParseTilesets(
        tinyxml2::XMLElement& tilesetRoot,
        const std::vector<Tileset>& tilesets)
{

}

void LevelParser::ParseTileLayer(
    tinyxml2::XMLElement& tileElement,
    const std::vector<Layer*> layers,
    const std::vector<Tileset>& tilesets)
{

}