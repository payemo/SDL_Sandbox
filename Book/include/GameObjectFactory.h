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
    static GameObjectFactory* Instance();

public:
    bool RegisterType(const std::string& typeId, BaseCreator* creator);
    GameObject* Create(const std::string& typeId);

private:
    GameObjectFactory() {}
    ~GameObjectFactory() {}

    std::map<std::string, BaseCreator*> m_creators;

private:
    static GameObjectFactory* m_instance;
};

typedef GameObjectFactory TheGameObjectFactory;