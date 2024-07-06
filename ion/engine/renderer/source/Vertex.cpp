#include "Vertex.h"

namespace ion
{
	Vertex::Vertex
	(
		const math::Vector3f& position,
		const math::Vector3f& normal,
		const math::Vector2f& textureCoords
	)
		: m_position(position), m_normal(normal), m_textureCoords(textureCoords)
	{
	}

	Vertex::Vertex(const math::Vector3f& position, const math::Vector3f& normal)
		: m_position(position), m_normal(normal)
	{
		m_textureCoords.X() = 0.f;
		m_textureCoords.Y() = 0.f;
	}

	Vertex::Vertex(const math::Vector3f& position, const math::Vector2f& textureCoords)
		: m_position(position), m_textureCoords(textureCoords)
	{

		m_normal.X() = 0.f;
		m_normal.Y() = 0.f;
		m_normal.Z() = 0.f;

	}

	Vertex::Vertex(const math::Vector3f& position)
		: m_position(position)
	{
		m_textureCoords.X() = 0.f;
		m_textureCoords.Y() = 0.f;

		m_normal.X() = 0.f;
		m_normal.Y() = 0.f;
		m_normal.Z() = 0.f;
	}

	Vertex::Vertex(const Vertex& other)
		: m_position(other.m_position), m_normal(other.m_normal),
		m_textureCoords(other.m_textureCoords)
	{
	}

	math::Vector3f& Vertex::Position(void)
	{
		return m_position;
	}

	math::Vector3f& Vertex::Normal(void)
	{
		return m_normal;
	}

	math::Vector2f& Vertex::TextureCoords(void)
	{
		return m_textureCoords;
	}

	math::Vector3f Vertex::GetPosition(void) const
	{
		return m_position;
	}

	math::Vector3f Vertex::GetNormal(void) const
	{
		return m_normal;
	}

	math::Vector2f Vertex::GetTextureCoords(void) const
	{
		return m_textureCoords;
	}

	Vertex& Vertex::operator=(const Vertex& rhs)
	{
		m_position = rhs.m_position;
		m_normal = rhs.m_normal;
		m_textureCoords = rhs.m_textureCoords;

		return *this;
	}


	bool Vertex::operator==(const Vertex& rhs)
	{
		return	m_position == rhs.m_position &&
				m_normal == rhs.m_normal &&
				m_textureCoords == rhs.m_textureCoords;
	}

	bool Vertex::operator!=(const Vertex& rhs)
	{
		return !(*this == rhs);
	}




	}