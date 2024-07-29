#pragma once

#include <inttypes.h>

namespace ion
{
	class EntityManager;

	class IComponent
	{
	public:

		using FlagType = uint64_t;

		enum EComponentType : FlagType
		{
			ECT_TRANSFORM		= 1,
			ECT_MODEL			= 1 << 1
		};

		enum EParentAttribute : int32_t
		{
			EPA_INVALID_PARENT	= -1
		};

	protected:

				IComponent(void) = default;
	virtual		~IComponent(void) = default;

	};



	template <typename TValueType>
	class Component : private IComponent
	{
	public:
		inline Component(void) = default;
		inline Component(int32_t entity, int32_t parentComponent);

		inline ~Component(void) = default;

		inline TValueType& Data(void);

		inline TValueType& operator*(void);
		inline TValueType* operator->(void);

	private:

		TValueType		m_data;
		int32_t			m_parentComponent = -1;
		int32_t			m_entity = 0;
		bool			m_enabled = false;
	};


	template <typename TValueType> inline
	Component<TValueType>::Component(int32_t entity, int32_t parentComponent)
		: m_entity(entity), m_parentComponent(parentComponent)
	{
	}


	template <typename TValueType> inline
	TValueType& Component<TValueType>::Data(void)
	{
		return m_data;
	}


	template <typename TValueType> inline
	TValueType& Component<TValueType>::operator*(void)
	{
		return m_data;
	}


	template <typename TValueType> inline
	TValueType* Component<TValueType>::operator->(void)
	{
		return &m_data;
	}

}