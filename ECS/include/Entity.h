#pragma once

//#include "Component.h"
#include "ComponentGeneric.h"
//#include "SmartRef.h"
//#include "Component.h"




namespace ion
{
	template<typename TRefType>
	class SmartRef;

	template <CComponent TComponentType>
	class ComponentArray;

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

		template<CComponent TComponentType> inline
		SmartRef<TComponentType> GetSmartComponent(void);

	private:

		IComponent::FlagType	m_componentFlags = 0;
		int32_t					m_index = 0;
		int32_t					m_parentIndex = IComponent::EPA_INVALID_PARENT;

	};


	template<typename TRefType>
	class SmartRef
	{
	private:

		inline void Refresh(void);
		inline void SetNewIndex(int32_t index);

		inline void Invalidate(void);

		static inline void RefreshAll(void);
		static inline void InvalidateAll(void);

	public:

		inline SmartRef(void) = delete;
		inline SmartRef(TRefType& ref, int32_t index);
		inline SmartRef(const SmartRef& other);

		inline ~SmartRef(void);

		inline TRefType* operator->(void);
		inline TRefType& operator*(void);

		inline SmartRef& operator=(const SmartRef& rhs);

		inline bool operator==(const TRefType& rhs) const;
		inline bool operator==(const SmartRef& rhs) const;

	private:

		TRefType*		m_ref;
		int32_t				m_index;

		static std::vector<SmartRef*>  m_allRefs;

		friend class ComponentArray<TRefType>;

	};



	template <>
	class SmartRef<Entity>
	{
	private:

		SmartRef(void) = delete;


		void Refresh(void);
		void SetNewIndex(int32_t index);

		void Invalidate(void);

		static void RefreshAll(void);
		static void InvalidateAll(void);

	public:

		SmartRef(Entity& ref);
		SmartRef(const SmartRef& other);

		~SmartRef(void);

		Entity* operator->(void);
		Entity& operator*(void);

		SmartRef& operator=(const SmartRef& rhs);

		bool operator==(const Entity& rhs) const;
		bool operator==(const SmartRef& rhs) const;

	private:

		Entity* m_ref;
		int32_t				m_index;

		static std::vector<SmartRef*>  m_allRefs;

		friend class EntityManager;
	};






	template<typename TRefType>
	std::vector<SmartRef<TRefType>*> SmartRef<TRefType>::m_allRefs;

	template<typename TRefType>
	inline SmartRef<TRefType>::SmartRef(TRefType& ref, int32_t index)
		: m_ref(&ref), m_index(index)
	{
		m_allRefs.push_back(this);
	}

	template<typename TRefType>
	inline SmartRef<TRefType>::SmartRef(const SmartRef& other)
		: m_ref(other.m_ref), m_index(other.m_index)
	{
		m_allRefs.push_back(this);
	}

	template<typename TRefType>
	inline SmartRef<TRefType>::~SmartRef(void)
	{
		Invalidate();
	}

	template<typename TRefType>
	inline void SmartRef<TRefType>::Refresh(void)
	{
		m_ref = /*nullptr;*/ &(EntityManager::GetComponentFromIndex<TRefType>(m_index));
	}

	template<typename TRefType>
	inline void SmartRef<TRefType>::SetNewIndex(int32_t index)
	{
		m_index = index;
		Refresh();
	}

	template<typename TRefType>
	inline void SmartRef<TRefType>::Invalidate(void)
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

	template<typename TRefType>
	inline void SmartRef<TRefType>::RefreshAll(void)
	{
		for (SmartRef* ref : m_allRefs)
			ref->Refresh();
	}

	template<typename TRefType>
	inline void SmartRef<TRefType>::InvalidateAll(void)
	{
		for (SmartRef* ref : m_allRefs)
			ref->Invalidate();
	}

	template<typename TRefType>
	inline TRefType* SmartRef<TRefType>::operator->(void)
	{
		return m_ref;
	}

	template<typename TRefType>
	inline TRefType& SmartRef<TRefType>::operator*(void)
	{
		return *m_ref;
	}


	template<typename TRefType>
	inline SmartRef<TRefType>& SmartRef<TRefType>::operator=(const SmartRef& rhs)
	{
		m_index = rhs.m_index;
		m_ref = rhs.m_ref;
	}

	template<typename TRefType>
	inline bool SmartRef<TRefType>::operator==(const TRefType& rhs) const
	{
		return m_ref == &rhs;
	}

	template<typename TRefType>
	inline bool SmartRef<TRefType>::operator==(const SmartRef& rhs) const
	{
		return m_index == rhs.m_index;
	}





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


	template<CComponent TComponentType>
	inline SmartRef<TComponentType> Entity::GetSmartComponent(void)
	{
		int32_t			refIndex = EntityManager::GetEntityComponentIndex<TComponentType>(m_index);
		TComponentType& component = EntityManager::GetEntityComponent<TComponentType>(*this);

		return SmartRef(component, refIndex);

	}










	//std::vector<SmartRef<Entity>*> SmartRef<Entity>::m_allRefs;

	//









}