#include "StateParser.h"
#include "TextureManager.h"
#include "Game.h"
#include "GameObjectFactory.h"

bool StateParser::ParseState(
        const char* stateFile,
        const std::string& stateId,
        std::vector<GameObject*>& objects,
        std::vector<std::string>& textureIds)
{
    tinyxml2::XMLDocument xmlDoc;

    if (xmlDoc.LoadFile(stateFile) == tinyxml2::XML_SUCCESS) {
        tinyxml2::XMLElement* root = xmlDoc.RootElement();

        if (root) {
            tinyxml2::XMLElement* stateRoot = GetXmlElement(*root, stateId);

            if (stateRoot) {
                // Parse textures
                {
                    tinyxml2::XMLElement* textureRoot = GetXmlElement(*stateRoot, "TEXTURES");

                    if (textureRoot) {
                        ParseTextures(*textureRoot, textureIds);
                    }
                }
                // Parse objects
                {
                    tinyxml2::XMLElement* objectRoot = GetXmlElement(*stateRoot, "OBJECTS");

                    if (objectRoot) {
                        ParseObjects(*objectRoot, objects);
                    }
                }
                return true;
            }
        }
        return false;
    }
    else {
        std::cerr << xmlDoc.ErrorStr() << std::endl;
        return false;
    }
}

void StateParser::ParseObjects(
        tinyxml2::XMLElement& stateRoot,
        std::vector<GameObject*>& objects)
{
    tinyxml2::XMLElement* el = stateRoot.FirstChildElement();

    while (el != nullptr) {
        int x, y, w, h, numFrames, callbackId, animationSpeed;
        std::string textureId;

        x = el->IntAttribute("x");
        y = el->IntAttribute("y");
        w = el->IntAttribute("width");
        h = el->IntAttribute("height");
        numFrames = el->IntAttribute("numFrames");
        callbackId = el->IntAttribute("callbackID");
        animationSpeed = el->IntAttribute("animSpeed");
        textureId = el->Attribute("textureID");

        GameObject* gameObject = TheGameObjectFactory::Instance()->Create(el->Attribute("type"));
        gameObject->Load(
            *(new LoaderParams(x, y, w, h, textureId, numFrames, callbackId, animationSpeed)));

        objects.push_back(gameObject);

        el = el->NextSiblingElement();
    }
}

void StateParser::ParseTextures(
    tinyxml2::XMLElement& stateRoot,
    std::vector<std::string>& textureIds)
{
    tinyxml2::XMLElement* el = stateRoot.FirstChildElement();

    while (el != nullptr) {
        std::string fileNameAttr = el->Attribute("filename");
        std::string idAttr = el->Attribute("ID");

        textureIds.push_back(idAttr);

        TheTextureManager::Instance()->Load(fileNameAttr, idAttr, TheGame::Instance()->GetRenderer());

        el = el->NextSiblingElement();
    }
}


tinyxml2::XMLElement* StateParser::GetXmlElement(
    tinyxml2::XMLElement& root,
    const std::string& name)
{
    tinyxml2::XMLElement* foundElement = nullptr;
    tinyxml2::XMLElement* child = root.FirstChildElement();

    while (child != nullptr) {
        if (child->Value() == name) {
            foundElement = child;
            break;
        }
        child = child->NextSiblingElement();
    }

    return foundElement;
}