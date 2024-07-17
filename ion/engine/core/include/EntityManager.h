#pragma once

#include <unordered_map>
#include <vector>

#include "Component.h"
#include "ComponentGeneric.h"
#include "ComponentArrayGeneric.h"
//#include "Component.h"

#include "Entity.h"
#include "Transform.h"

#include <iostream>


namespace ion
{

	class EntityManager
	{
	public:

		static Entity& CreateEntity(void);
		static Entity& CreateChildEntity(const Entity& parent);

		template <CComponent TComponentType> inline static
		TComponentType& CreateComponent(const Entity& entity);

		template <CComponent TComponentType> inline  static
		TComponentType& GetComponentFromIndex(int32_t index);


		template <CComponent TComponentType> inline static
		TComponentType& GetEntityComponent(const Entity& entity);

		static Entity& GetEntity(int32_t index);

	private:

		static std::vector<Entity>			m_entities;
		static ComponentArray<Transform>	m_transformArray;


	};





	template<>
	inline Transform& EntityManager::CreateComponent<Transform>(const Entity& entity)
	{
		m_transformArray.MapEntityToComponent(entity.Index(), m_transformArray.Size());

		int32_t parentID = entity.Parent();

		if (parentID == IComponent::EPA_INVALID_PARENT)
			return m_transformArray.EmplaceBack(entity.Index(), parentID);

		Entity& parentEntity = m_entities[parentID];

		if (parentEntity.Flags() & IComponent::ECT_TRANSFORM)
		{
			int32_t parentComponent = m_transformArray.GetEntityComponentIndex(parentID);

			Transform& newTransform = m_transformArray.EmplaceBack(entity.Index(), parentComponent);

			newTransform.m_parent = parentComponent;
			return newTransform;
		}

		return m_transformArray.EmplaceBack(entity.Index(), IComponent::EPA_INVALID_PARENT);

	}

	template<>
	inline Transform& EntityManager::GetComponentFromIndex(int32_t index)
	{
		return m_transformArray.GetComponentFromIndex(index);
	}

	template<>
	inline Transform& EntityManager::GetEntityComponent<Transform>(const Entity& entity)
	{
		return m_transformArray.GetEntityComponent(entity.Index());
	}









}