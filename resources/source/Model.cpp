#include <fstream>

#include "IonDebug.hpp"

#include "Model.h"
#include "ModelImporter.h"

namespace ion
{
	Model::Model(Model&& other) noexcept
	{
		m_indices = std::move(other.m_indices);
		m_vertices = std::move(other.m_vertices);

	}

	bool Model::ImportWavefront(const std::filesystem::path& path)
	{

		WavefrontImporter reader(this);

		return reader.LoadModel(path);

	}

	bool Model::ImportManually(std::vector<Vertex>&& vertices, std::vector<uint32_t>&& indices) noexcept
	{
		m_vertices = std::forward<std::vector<Vertex>&&>(vertices);
		m_indices = std::forward<std::vector<uint32_t>&&>(indices);

		if (!m_indices.size())
		{
			ION_LOG_ERROR("Missing indices");
			return false;
		}

		if (!m_vertices.size())
		{
			ION_LOG_ERROR("Missing vertices");
			return false;
		}

		return true;
	}


	// TODO: use custom format for accurate re-reading
	bool Model::Export(const std::filesystem::path& path) const
	{
		std::ofstream	output(path, std::ios::out);

		if (!output)
			return false;

		for (const Vertex& vertex : m_vertices)
		{
			output << "v " << vertex.GetPosition() << '\n';
			output << "vt " << vertex.GetTextureCoords() << '\n';
			output << "vn " << vertex.GetNormal() << '\n';
		}

		return true;
	}


	Model& Model::operator=(const Model& rhs)
	{
		m_indices = rhs.m_indices;
		m_vertices = rhs.m_vertices;

		return *this;
	}


	Model& Model::operator=(Model&& rhs) noexcept
	{
		m_indices = std::move(rhs.m_indices);
		m_vertices = std::move(rhs.m_vertices);

		return *this;
	}
}