/*

 _____                               _
|_   _|                             (_)
  | |  ___  _ __     ___ _ __   __ _ _ _ __   ___
  | | / _ \| '_ \   / _ \ '_ \ / _` | | '_ \ / _ \
 _| || (_) | | | | |  __/ | | | (_| | | | | |  __/
 \___/\___/|_| |_|  \___|_| |_|\__, |_|_| |_|\___|
								__/ |
							   |___/


NAME: Model.h

DESCTIPTION: 3D model loaded from a file

AUTHOR: Noah de Pischof | @torrra on GitHub


STYLE:

E is used as a prefix for enums

*/



#pragma once

#include <vector>
#include <filesystem>

#include "math/Vector3.hpp"
#include "math/Vector2.hpp"

#include "Vertex.h"

namespace ion
{

	class Model final
	{
	private:

		class WavefrontImporter;

		friend class VertexArray;

	public:

						Model(void) = default;
						Model(const Model& other) = default;
						Model(Model&& other) noexcept;


						~Model(void) = default;

		// Read from a wavefront OBJ file
		bool			ImportWavefront(const std::filesystem::path& path);

		// Initialize model from in-source vectors
		bool			ImportManually(std::vector<Vertex>&& vertices, std::vector<uint32_t>&& indices) noexcept;


		// Write data back into a plain text file
		bool			Export(const std::filesystem::path& path)	const;


		Model&			operator=(const Model& rhs);
		Model&			operator=(Model&& rhs)						noexcept;


	private:

		std::vector<Vertex>		m_vertices;
		std::vector<uint32_t>	m_indices;

	};

}