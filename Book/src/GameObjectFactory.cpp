#include <iostream>
#include "GameObjectFactory.h"

bool GameObjectFactory::RegisterType(const std::string& typeId, BaseCreator* creator)
{
    auto it = m_creators.find(typeId);

    if (it != m_creators.end()) {
        delete creator;
        return false;
    }

    m_creators[typeId] = creator;
    return true;
}

GameObject* GameObjectFactory::Create(const std::string& typeId)
{
    auto it = m_creators.find(typeId);

    if (it == m_creators.end()) {
        std::cout << "Can't find type: " << typeId << std::endl;
        return nullptr;
    }

    BaseCreator* creator = (*it).second;
    return creator->Create();

}