#pragma once

#include <vector>
#include <filesystem>

#include "math/Vector3.hpp"
#include "math/Vector2.hpp"

#include "Vertex.h"

namespace ion
{

	enum EModelProperties : uint8_t
	{
		ROOT				= 1,
		TEXTURE				= 1 << 1,
		MATERIAL			= 1 << 2,
		DIFFUSE				= 1 << 3,
		GLOW				= 1 << 4,
		NORMAL_MAP			= 1 << 5,
		NORMAL_TANGENT		= 1 << 6,
		SPECULAR			= 1 << 7

	};


	class Model final
	{
	private:

		using FlagType		= uint8_t;

		class Importer;

	public:

						Model(void) = default;
						Model(const Model& other) = default;
						Model(Model&& other) noexcept;


						~Model(void) = default;

		// Read from a wavefront OBJ file
		bool			Import(const std::filesystem::path& path);


		// Write data back into a plain text file
		bool			Export(const std::filesystem::path& path)	const;


		Model&			operator=(const Model& rhs);
		Model&			operator=(Model&& rhs)						noexcept;


	private:

		std::vector<Vertex>		m_vertices;
		std::vector<uint32_t>	m_indices;

		FlagType				m_properties = 0;
	};

}