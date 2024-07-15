#include "Entity.h"
#include "EntityManager.h"

namespace ion
{
	Entity::Entity(int32_t index)
		: m_index(index)
	{
	}

	Entity::Entity(int32_t index, int32_t parent)
		: m_index(index), m_parentIndex(parent)
	{
	}


	IComponent::FlagType Entity::Flags(void) const
	{
		return m_componentFlags;
	}


	int32_t Entity::Index(void) const
	{
		return m_index;
	}


	int32_t Entity::Parent(void) const
	{
		return m_parentIndex;
	}


	Entity& Entity::CreateChild(void) const
	{
		return EntityManager::CreateChildEntity(*this);
	}
}