#include <vector>
#include "zlib.h"
#include "base64.h"
#include "LevelParser.h"
#include "Level.h"
#include "TextureManager.h"
#include "Game.h"
#include "TileLayer.h"
#include "ObjectLayer.h"
#include "GameObjectFactory.h"

Level& LevelParser::ParseLevel(const char* levelFile)
{
    tinyxml2::XMLDocument levelDocument;
    levelDocument.LoadFile(levelFile);

    // Create level object
    Level* level = new Level;

    tinyxml2::XMLElement* root = levelDocument.RootElement();

    m_tileSize = root->IntAttribute("tilewidth");
    m_width = root->IntAttribute("width");
    m_height = root->IntAttribute("height");

    // Parse textures
    {
        tinyxml2::XMLElement* properties = root->FirstChildElement();
        tinyxml2::XMLElement* child = properties->FirstChildElement();

        while (child != nullptr) {
            if (child->Value() == std::string("property")) {
                ParseTextures(*child);
            }
            child = child->NextSiblingElement();
        }
    }

    // Parse the tilesets
    {
        tinyxml2::XMLElement* child = root->FirstChildElement();
        while (child != nullptr) {
            if (child->Value() == std::string("tileset")) {
                level->AddTileset(ParseTileset(*child));
            }
            child = child->NextSiblingElement();
        }
    }

    // Parse anyy object layer
    {
        tinyxml2::XMLElement* child = root->FirstChildElement();
        while (child != nullptr) {
            if (child->Value() == std::string("objectgroup") ||
                child->Value() == std::string("layer")) {

                if (child->FirstChildElement()->Value() == std::string("object")) {
                    ParseObjectLayer(*child, level->GetLayers());
                }

                if (child->FirstChildElement()->Value() == std::string("data")) {
                    Layer& layer = ParseTileLayer(*child, level->GetTilesets());
                    level->AddLayer(&layer);
                }
            }
            
            child = child->NextSiblingElement();
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
    tileset.name = tilesetRoot.Attribute("name");

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
            if (child->Value() == std::string("data")) {
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

                node = node->NextSiblingElement();
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

void LevelParser::ParseTextures(tinyxml2::XMLElement& textureRoot)
{
    auto value = textureRoot.Attribute("value");
    auto name = textureRoot.Attribute("name");
    TheTextureManager::Instance()->Load(value, name, TheGame::Instance()->GetRenderer());
}

void LevelParser::ParseObjectLayer(tinyxml2::XMLElement& objectElement, std::vector<Layer*>& layers)
{
    // Cteate object layer
    ObjectLayer* objectLayer = new ObjectLayer;

    std::cout << objectElement.FirstChildElement()->Value() << std::endl;

    tinyxml2::XMLElement* child = objectElement.FirstChildElement();
    
    while (child != nullptr) {
        std::cout << child->Value() << std::endl;

        if (child->Value() == std::string("object")) {
            int x, y, w, h, numFrames, callbackId = 0, animSpeed = 0;
            std::string textureId;
            std::string type;

            x = child->IntAttribute("x");
            y = child->IntAttribute("y");
            type = child->Attribute("type");

            GameObject* gameObject = TheGameObjectFactory::Instance()->Create(type);

            // get property values
            tinyxml2::XMLElement* properties = child->FirstChildElement();

            while (properties != nullptr) {
                if (properties->Value() == std::string("properties")) {
                    tinyxml2::XMLElement* prop = properties->FirstChildElement();

                    while (prop != nullptr) {
                        if (prop->Value() == std::string("property")) {
                            if (prop->Attribute("name") == std::string("numFrames")) {
                                numFrames = prop->IntAttribute("value");
                            }
                            else if (prop->Attribute("name") == std::string("textureHeight")) {
                                h = prop->IntAttribute("value");
                            }
                            else if (prop->Attribute("name") == std::string("textureID")) {
                                textureId = prop->Attribute("value");
                            }
                            else if (prop->Attribute("name") == std::string("textureWidth")) {
                                w = prop->IntAttribute("value");
                            }
                            else if (prop->Attribute("name") == std::string("callbackID")) {
                                callbackId = prop->IntAttribute("value");
                            }
                            else if (prop->Attribute("name") == std::string("animSpeed")) {
                                animSpeed = prop->IntAttribute("value");
                            }
                        }
                        prop = prop->NextSiblingElement();
                    }
                }
                properties = properties->NextSiblingElement();
            }
            gameObject->Load(
                *(new LoaderParams(x, y, w, h, textureId, numFrames, callbackId, animSpeed)));

            objectLayer->GetGameObjects().push_back(gameObject);
        }
        child = child->NextSiblingElement();
    }
    layers.push_back(objectLayer);
}