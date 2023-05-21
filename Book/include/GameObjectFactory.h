#pragma once

#include <string>
#include <map>
#include "GameObject.h"

class BaseCreator
{
public:
    virtual GameObject* Create() const = 0;
    virtual ~BaseCreator() {}
};

class GameObjectFactory
{
public:
    bool RegisterType(const std::string& typeId, BaseCreator* creator);
    GameObject* Create(const std::string& typeId);

private:
    std::map<std::string, BaseCreator*> m_creators;
};