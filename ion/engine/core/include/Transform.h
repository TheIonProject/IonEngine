#pragma once

#include "Component.h"

#include "math/Vector3.hpp"
#include "math/Matrix4.hpp"

namespace ion
{

	class  Transform
	{
	public:


							Transform(void) = default;
							~Transform(void) = default;

		math::Matrix4f		LocalMatrix(void)		const;
		math::Matrix4f		GlobalMatrix(void)		const;



	private:

		void				UpdateGlobalMatrix(void);
		void				UpdateLocalMatrix(void);


		math::Matrix4f		m_globalTransform;
		//math::Matrix4f		m_localTransform;

		math::Vector3f		m_localPosition{ 0.f };
		math::Vector3f		m_localScale{ 1.f };
		math::Vector3f		m_localRotation{ 0.f };

		int32_t				m_parent = IComponent::EPA_INVALID_PARENT;

	};

	using TransformComponent = Component<Transform>;
}