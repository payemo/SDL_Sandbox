#include <vector>
#include "zlib.h"
#include "base64.h"
#include "LevelParser.h"
#include "Level.h"
#include "TextureManager.h"
#include "Game.h"
#include "TileLayer.h"

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
                Layer& layer = ParseTileLayer(*child, level->GetTilesets());
                level->AddLayer(&layer);
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

TileLayer& LevelParser::ParseTileLayer(
    tinyxml2::XMLElement& tileElement,
    const std::vector<Tileset>& tilesets)
{
    TileLayer* tileLayer = new TileLayer(m_tileSize, tilesets);

    std::vector<std::vector<int>> data;

    std::string decodeIds;

    {
        tinyxml2::XMLElement* dataNode = nullptr;
        tinyxml2::XMLElement* child = tileElement.FirstChildElement();

        while (child != nullptr) {
            if (child->Value() == "data") {
                dataNode = child;
                break;
            }
            child = child->NextSiblingElement();
        }

        if (dataNode) {
            tinyxml2::XMLNode* node = dataNode->FirstChild();

            while (node != nullptr) {
                tinyxml2::XMLText* text = node->ToText();
                std::string s = text->Value();
                decodeIds = base64_decode(s);
            }
        }
    }

    uLongf sizeofids = m_width * m_height * sizeof(int);
    std::vector<int> ids(m_width * m_height);
    uncompress((Bytef*)&ids[0], &sizeofids, (const Bytef*)decodeIds.c_str(), decodeIds.size());
    
    std::vector<int> layerRow(m_width);

    for (int i = 0; i < m_height; ++i) {
        data.push_back(layerRow);
    }

    for (int row = 0; row < m_height; ++row) {
        for (int col = 0; col < m_width; ++col) {
            data[row][col] = ids[row * m_width + col];
        }
    }

    tileLayer->SetTileIds(data);

    return *tileLayer;
}