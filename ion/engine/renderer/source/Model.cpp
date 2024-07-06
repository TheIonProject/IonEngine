#include <fstream>

#include "Model.h"
#include "ModelImporter.h"

namespace ion
{
	Model* Model::Import(const std::filesystem::path& path)
	{

		Importer reader(path);

		return reader.LoadModel();

	}


	// TODO: use custom format for accurate re-reading
	bool Model::Export(const std::filesystem::path& path)
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
}