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




	std::vector<SmartRef<Entity>*> SmartRef<Entity>::m_allRefs;


	SmartRef<Entity>::SmartRef(Entity& ref)
		: m_ref(&ref), m_index(ref.Index())
	{
		m_allRefs.push_back(this);
	}


	SmartRef<Entity>::SmartRef(const SmartRef& other)
		: m_ref(other.m_ref), m_index(other.m_index)
	{
		m_allRefs.push_back(this);
	}


	SmartRef<Entity>::~SmartRef(void)
	{
		Invalidate();
	}

	void SmartRef<Entity>::Refresh(void)
	{
		m_ref = /*nullptr;*/ &(EntityManager::GetEntity(m_index));
	}

	void SmartRef<Entity>::SetNewIndex(int32_t index)
	{
		m_index = index;
		Refresh();
	}

	void SmartRef<Entity>::Invalidate(void)
	{
		auto refIt = m_allRefs.begin();

		while (refIt != m_allRefs.end())
		{
			if (*refIt == this)
			{
				m_allRefs.erase(refIt);
				break;
			}

			++refIt;
		}

		m_index = -1;
		m_ref = nullptr;
	}

	void SmartRef<Entity>::RefreshAll(void)
	{
		for (SmartRef* ref : m_allRefs)
			ref->Refresh();
	}

	void SmartRef<Entity>::InvalidateAll(void)
	{
		for (SmartRef* ref : m_allRefs)
			ref->Invalidate();
	}

	Entity* SmartRef<Entity>::operator->(void)
	{
		return m_ref;
	}

	Entity& SmartRef<Entity>::operator*(void)
	{
		return *m_ref;
	}


	SmartRef<Entity>& SmartRef<Entity>::operator=(const SmartRef& rhs)
	{
		m_index = rhs.m_index;
		m_ref = rhs.m_ref;
		return *this;
	}


	bool SmartRef<Entity>::operator==(const Entity& rhs) const
	{
		return m_ref == &rhs;
	}

	bool SmartRef<Entity>::operator==(const SmartRef& rhs) const
	{
		return m_index == rhs.m_index;
	}

}