#include "Transform.h"
#include "EntityManager.h"

namespace ion
{
	math::Matrix4f	Transform::LocalMatrix() const
	{
		math::Matrix4f scale(1.f);

		scale[0][0] = m_localScale[0];
		scale[1][1] = m_localScale[1];
		scale[2][2] = m_localScale[2];


		math::Matrix4f rotation = math::Matrix4f::RotationMatrix(m_localRotation);


		math::Matrix4f translation(1.f);

		translation[3][0] = m_localPosition[0];
		translation[3][1] = m_localPosition[1];
		translation[3][2] = m_localPosition[2];

		return  translation * rotation * scale;
	}


	// TODO
	math::Matrix4f	Transform::GlobalMatrix() const
	{
		return m_globalTransform;

	}


	math::Vector3f& Transform::Position(void)
	{
		return m_localPosition;
	}

	math::Vector3f& Transform::Rotation(void)
	{
		return m_localRotation;
	}

	math::Vector3f& Transform::Scale(void)
	{
		return m_localScale;
	}


	void Transform::UpdateLocalMatrix(void)
	{

	}

	void Transform::UpdateGlobalMatrix(void)
	{
		if (m_parent == IComponent::EPA_INVALID_PARENT)
			m_globalTransform = LocalMatrix();


		else
		{
			Transform& parent = EntityManager::GetComponentFromIndex<Transform>(m_parent);

			m_globalTransform = parent.m_globalTransform * LocalMatrix();
		}

	}

}