#include "LevelParser.h"
#include "Level.h"
#include "TextureManager.h"
#include "Game.h"

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
                level->AddTileset(ParseTileset(*child));
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

    return *level;
}

const Tileset& LevelParser::ParseTileset(tinyxml2::XMLElement& tilesetRoot)
{
    std::string sourceName = tilesetRoot.FirstChildElement()->Attribute("source");
    std::string tilesetName = tilesetRoot.Attribute("name");
    TheTextureManager::Instance()->Load(sourceName, tilesetName, TheGame::Instance()->GetRenderer());

    // Create a tileset object
    Tileset tileset;
    tileset.width = tilesetRoot.FirstChildElement()->IntAttribute("width");
    tileset.height = tilesetRoot.FirstChildElement()->IntAttribute("height");
    tileset.firstGridId = tilesetRoot.IntAttribute("firstgid");
    tileset.tileWidth = tilesetRoot.IntAttribute("tilewidth");
    tileset.tileHeight = tilesetRoot.IntAttribute("tileheight");
    tileset.spacing = tilesetRoot.IntAttribute("spacing");
    tileset.margin = tilesetRoot.IntAttribute("margin");
    tileset.name = tilesetRoot.IntAttribute("name");

    tileset.numColumns = tileset.width / (tileset.width + tileset.spacing);

    return tileset;
}

void LevelParser::ParseTileLayer(
    tinyxml2::XMLElement& tileElement,
    const std::vector<Layer*>& layers,
    const std::vector<Tileset>& tilesets)
{

}