#pragma once

#include <iostream>
#include <vector>
#include "tinyxml2.h"

class GameObject;

class StateParser
{
public:
    bool ParseState(
        const char* stateFile, 
        const std::string& stateId, 
        std::vector<GameObject*>& objects,
        std::vector<std::string>& textureIds);

private:
    void ParseObjects(
        tinyxml2::XMLElement& stateRoot,
        std::vector<GameObject*>& objects);

    void ParseTextures(
        tinyxml2::XMLElement& stateRoot,
        std::vector<std::string>& textureIds);

    tinyxml2::XMLElement* GetXmlElement(
        tinyxml2::XMLElement& root,
        const std::string& name);
};