#pragma once

#include <tuple>

#include"IComponent.h"
#include "ComponentGeneric.h"
//#include "Component.h"

namespace ion
{
	class Entity
	{
	public:
				Entity(void) = delete;
	explicit	Entity(int32_t index);
	explicit	Entity(int32_t index,  int32_t parent);

		~Entity(void) = default;

		IComponent::FlagType Flags(void) const;

		int32_t				 Index(void) const;
		int32_t				 Parent(void) const;

		Entity&				 CreateChild(void) const;

		template <CComponent TComponentType>
		TComponentType&		GetComponent(void);

		template <CComponent TComponentType>
		TComponentType&		AddComponent();

	private:

		IComponent::FlagType	m_componentFlags = 0;
		int32_t					m_index = 0;
		int32_t					m_parentIndex = IComponent::EPA_INVALID_PARENT;

	};



	template<CComponent TComponentType>
	inline TComponentType& Entity::GetComponent(void)
	{
		if (m_componentFlags & ComponentTraits<TComponentType>::flag)
			return EntityManager::GetEntityComponent<TComponentType>(*this);

		else
			throw std::exception("This entity does not have the requested component");
	}


	template<CComponent TComponentType>
	inline TComponentType& Entity::AddComponent()
	{
		if (m_componentFlags & ComponentTraits<TComponentType>::flag)
			return EntityManager::GetEntityComponent<TComponentType>(*this);

		else
		{
			m_componentFlags |= IComponent::ECT_TRANSFORM;
			return EntityManager::CreateComponent<TComponentType>(*this);
		}

	}
}