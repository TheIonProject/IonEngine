#include "EntityManager.h"
#include "IonDebug.hpp"

namespace ion
{
    std::vector<Entity>			EntityManager::m_entities;
    ComponentArray<Transform>	EntityManager::m_transformArray;


    Entity& EntityManager::CreateEntity(void)
    {
        int32_t     index = static_cast<int32_t>(m_entities.size());

        Entity& entity = m_entities.emplace_back(index);

        SmartRef<Entity>::RefreshAll();

        return entity;
    }


    Entity& EntityManager::GetEntity(int32_t index)
    {
        ION_ASSERT(index != IComponent::EPA_INVALID_PARENT);
        ION_ASSERT(index < m_entities.size());

        return m_entities[index];
    }


    Entity& EntityManager::CreateChildEntity(const Entity& parent)
    {
        int32_t     index = static_cast<int32_t>(m_entities.size());

        Entity& entity = m_entities.emplace_back(index, parent.Index());

        SmartRef<Entity>::RefreshAll();

        return entity;
    }
}