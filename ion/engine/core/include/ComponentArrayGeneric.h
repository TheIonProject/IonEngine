#pragma once

#include <unordered_map>
#include <vector>

#include "ComponentGeneric.h"

namespace ion
{
	template <CComponent TComponentType>
	class ComponentArray
	{
	private:

		using Container			= Component<TComponentType>;
		using EntityID			= int32_t;
		using ComponentID		= int32_t;

	public:

		//inline TComponentType&		AddComponent(const Entity& entity);
		inline TComponentType&		GetEntityComponent(int32_t entityIndex);
		inline int32_t				GetEntityComponentIndex(int32_t entityIndex);
		inline TComponentType&		GetComponentFromIndex(int32_t componentIndex);

		inline bool					RemoveComponent(int32_t componentIndex);
		inline void					MapEntityToComponent(int32_t entityID, int32_t componentId);

		inline int32_t				Size();

		template <typename... Args>
		inline TComponentType&		EmplaceBack(Args... args);

		inline auto begin(void);
		inline auto end(void);

	private:

		std::unordered_map<EntityID, ComponentID>	m_entityMap;
		std::vector<Container>						m_components;

		friend class EntityManager;
	};







	template<CComponent TComponentType>
	inline TComponentType& ComponentArray<TComponentType>::GetEntityComponent(int32_t entityIndex)
	{
		int32_t		componentIndex = m_entityMap[entityIndex];

		return m_components[componentIndex].Data();
	}

	template<CComponent TComponentType>
	inline int32_t ComponentArray<TComponentType>::GetEntityComponentIndex(int32_t entityIndex)
	{
		return m_entityMap[entityIndex];
	}

	template<CComponent TComponentType>
	inline TComponentType& ComponentArray<TComponentType>::GetComponentFromIndex(int32_t componentIndex)
	{
		return m_components[componentIndex].Data();
	}

	template<CComponent TComponentType>
	inline void ComponentArray<TComponentType>::MapEntityToComponent(int32_t entityID, int32_t componentId)
	{
		m_entityMap[entityID] = componentId;
	}

	template<CComponent TComponentType>
	inline int32_t ComponentArray<TComponentType>::Size()
	{
		return static_cast<int32_t>(m_components.size());
	}

	template<CComponent TComponentType>
	inline auto ComponentArray<TComponentType>::begin(void)
	{
		return m_components.begin();
	}

	template<CComponent TComponentType>
	inline auto ComponentArray<TComponentType>::end(void)
	{
		return m_components.end();
	}

	template<CComponent TComponentType>
	template<typename ...Args>
	inline TComponentType& ComponentArray<TComponentType>::EmplaceBack(Args ...args)
	{
		return m_components.emplace_back(args...).Data();
	}
}