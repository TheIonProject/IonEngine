#include <fstream>

#include "Model.h"
#include "ModelImporter.h"

namespace ion
{
	Model::Model(Model&& other) noexcept
		: m_properties(other.m_properties), m_parent(other.m_parent)
	{
		m_indices = std::move(other.m_indices);
		m_vertices = std::move(other.m_vertices);

		other.m_properties = 0;
		other.m_parent = -1;
	}

	Model* Model::Import(const std::filesystem::path& path)
	{

		Importer reader(path);

		return reader.LoadModel();

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

		m_properties = rhs.m_properties;
		m_parent = rhs.m_parent;

		return *this;
	}


	Model& Model::operator=(Model&& rhs) noexcept
	{
		m_indices = std::move(rhs.m_indices);
		m_vertices = std::move(rhs.m_vertices);

		m_properties = rhs.m_properties;
		m_parent = rhs.m_parent;

		return *this;
	}
}