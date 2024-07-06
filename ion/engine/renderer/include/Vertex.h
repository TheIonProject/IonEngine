#pragma once

#include "math/Vector3.hpp"
#include "math/Vector2.hpp"

namespace ion
{
	class Vertex final
	{
	public:

		Vertex(void) = default;

		Vertex
		(
			const math::Vector3f& position,
			const math::Vector3f& normal,
			const math::Vector2f& textureCoords
		);

		Vertex
		(
			const math::Vector3f& position,
			const math::Vector3f& normal
		);

		Vertex
		(
			const math::Vector3f& position,
			const math::Vector2f& textureCoords
		);


		Vertex(const math::Vector3f& position);
		Vertex(const Vertex& other);


		~Vertex(void) = default;


		math::Vector3f&		Position(void);
		math::Vector3f&		Normal(void);
		math::Vector2f&		TextureCoords(void);


		math::Vector3f		GetPosition(void)			const;
		math::Vector3f		GetNormal(void)				const;
		math::Vector2f		GetTextureCoords(void)		const;


		Vertex&				operator=(const Vertex& rhs);
		bool			    operator==(const Vertex& rhs);
		bool				operator!=(const Vertex& rhs);


	private:

		math::Vector3f		m_position;
		math::Vector3f		m_normal;
		math::Vector2f		m_textureCoords;

	};

}