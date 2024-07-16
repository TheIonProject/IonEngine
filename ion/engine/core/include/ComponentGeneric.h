#pragma once

#include "Transform.h"
#include "Model.h"

namespace ion
{
	using Mesh = Component<Model>;

	template<typename TComponentType>
	struct IsValidComponent
	{
		static constexpr bool value = false;
	};


	template<>
	struct IsValidComponent<Transform>
	{
		static constexpr bool value = true;
	};

	template<>
	struct IsValidComponent<Mesh>
	{
		static constexpr bool value = true;
	};


	template <typename TComponentType>
	concept CComponent =
	IsValidComponent<TComponentType>::value;


	template <CComponent TComponentType>
	struct ComponentTraits
	{
		static constexpr IComponent::FlagType flag = 0;
	};

	template<>
	struct ComponentTraits<Transform>
	{
		static constexpr IComponent::FlagType flag = IComponent::ECT_TRANSFORM;
	};

}