#include "Transform.h"
#include "EntityManager.h"

namespace ion
{
	math::Matrix4f	Transform::LocalMatrix() const
	{
		math::Matrix4f result(1.f);

		result[0][0] = m_localScale[0];
		result[1][1] = m_localScale[1];
		result[2][2] = m_localScale[2];


		math::Matrix4f rotation = math::Matrix4f::RotationMatrix(m_localRotation);


		result = rotation * result;

		math::Matrix4f translation(1.f);

		translation[0][3] = m_localPosition[0];
		translation[0][3] = m_localPosition[1];
		translation[0][3] = m_localPosition[2];

		return translation * result;
	}


	// TODO
	math::Matrix4f	Transform::GlobalMatrix() const
	{
		return m_globalTransform;

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