/*

 _____                               _
|_   _|                             (_)
  | |  ___  _ __     ___ _ __   __ _ _ _ __   ___
  | | / _ \| '_ \   / _ \ '_ \ / _` | | '_ \ / _ \
 _| || (_) | | | | |  __/ | | | (_| | | | | |  __/
 \___/\___/|_| |_|  \___|_| |_|\__, |_|_| |_|\___|
								__/ |
							   |___/


NAME: Vertex.h

DESCTIPTION: Vertex class containing position, texture coordinates and vertex normal

AUTHOR: Noah de Pischof | @torrra on GitHub


STYLE:

m_ prefix is used to differentiate variables from local variables

*/



#pragma once

#include "IonCompiler.hpp"
#include <ResourceExport.h>

#include "math/Vector3.hpp"
#include "math/Vector2.hpp"

namespace ion
{
	class RES_API Vertex final
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

// TODO: something something needs to have dll interface blah blah
ION_PUSH_WARNINGS()
ION_DISABLE_WARNING(4251)

		math::Vector3f		m_position;
		math::Vector3f		m_normal;
		math::Vector2f		m_textureCoords;

ION_POP_WARNINGS()

	};

}