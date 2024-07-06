#include <iostream>
#include <fstream>
#include <vector>
#include <list>

#include "IonDebug.hpp"
#include "IonUtils.hpp"

#include "ModelImporter.h"

namespace ion
{

	bool Model::Importer::FileToBuffer(const std::filesystem::path& path, std::stringstream& buffer)
	{
		std::ifstream		fileStream(path, std::ios::in);

		if (!fileStream)
		{
			std::stringstream	message("Unable to open ");

			message << path.string() << ".\n";

			ION_LOG_ERROR(message.str());

			return false;
		}

		buffer << fileStream.rdbuf();

		return true;
	}

	void Model::Importer::PositionState(std::string& string, std::stringstream& objBuffer)
	{
		if (string.size() > 1)
		{
			switch (string[1])
			{
			case 't':
				TextureCoordState(string, objBuffer);
				return;

			case 'n':
				NormalState(string, objBuffer);
				return;

			default: break;
			}
		}


		float				x, y, z;
		std::stringstream	line;

		objBuffer >> string;

		while (std::string("+-0123456789").find(string[0]) != std::string::npos)
		{
			x = static_cast<float>(atof(string.c_str()));

			objBuffer >> y >> z >> string;

			m_positions.emplace_back(x, y, z);

		}
	}

	void Model::Importer::NormalState(std::string& string, std::stringstream& objBuffer)
	{
		float				x, y, z;
		std::stringstream	line;

		objBuffer >> string;

		while (std::string("-+0123456789").find(string[0]) != std::string::npos)
		{
			x = static_cast<float>(atof(string.c_str()));

			objBuffer >> y >> z >> string;

			m_normals.emplace_back(x, y, z);

		}
	}

	void Model::Importer::TextureCoordState(std::string& string, std::stringstream& objBuffer)
	{
		float				x, y;
		std::stringstream	line;

		objBuffer >> string;

		while (std::string("-+0123456789").find(string[0]) != std::string::npos)
		{
			x = static_cast<float>(atof(string.c_str()));

			objBuffer >> y >> string;

			m_texCoords.emplace_back(x, y);

		}
	}

	void Model::Importer::FaceState(std::string& line, std::stringstream& objBuffer)
	{
		std::vector<uint32_t>		vertexIndices;
		std::string					indexString;

		objBuffer >> indexString;

		while (true)
		{
			if (m_uniqueVertices.contains(indexString))
			{
				uint32_t		existingIndex = m_uniqueVertices[indexString];

				vertexIndices.push_back(existingIndex);
			}

			else
			{
				ProcessVertexIndices(indexString);

				uint32_t		newVertex = AddVertex();

				vertexIndices.push_back(newVertex);
				m_uniqueVertices[indexString] = newVertex;

			}

			indexString = std::string();
			objBuffer >> indexString;

			if (std::string("+-0123456789").find(indexString[0]) == std::string::npos)
				break;
		}

		AddFaceIndices(vertexIndices);

		if (objBuffer.eof())
			return;

		objBuffer.seekg(objBuffer.tellg() - static_cast<long long>(indexString.size()));
		objBuffer >> line;


	}

	void Model::Importer::AddFaceIndices(const std::vector<uint32_t>& vertexIndices)
	{
		switch (vertexIndices.size())
		{
		case 0: break;
		case 1:
		case 2:
			throw std::exception("Invalid face in model");

		case 3:
			m_currentModel->m_indices += vertexIndices;
			break;

		case 4:
			m_currentModel->m_indices += vertexIndices;
			m_currentModel->m_indices.push_back(vertexIndices[2]);
			m_currentModel->m_indices.push_back(vertexIndices[0]);
			break;

		default:
			for (size_t index = 1; index < vertexIndices.size() - 1; ++index)
			{
				m_currentModel->m_indices.push_back(vertexIndices[0]);
				m_currentModel->m_indices.push_back(vertexIndices[index]);

				if (index == vertexIndices.size() - 1)
					m_currentModel->m_indices.push_back(vertexIndices[1]);

				else
					m_currentModel->m_indices.push_back(vertexIndices[index + 1]);
			}
			break;
		}
	}

	void Model::Importer::ProcessVertexIndices(const std::string& faceString)
	{
		std::string		index;

		uint32_t			vertexAttribute = 0;
		size_t			character = 0;

		while (character < faceString.size())
		{
			if (faceString[character] == '/')
			{
				uint32_t convertedIndex = atoi(index.c_str());

				if (convertedIndex < 1)
					convertedIndex += NegativeToPositive(vertexAttribute);

				else
					convertedIndex -= 1;

				(*this)[vertexAttribute] = convertedIndex;


				index = std::string();

				++character;
				++vertexAttribute;

				continue;
			}

			index += faceString[character];
			++character;
		}

	}

	uint32_t Model::Importer::NegativeToPositive(uint32_t index)
	{
		switch (index)
		{
		case 0:
			return static_cast<uint32_t>(m_positions.size());

		case 1:
			return static_cast<uint32_t>(m_texCoords.size());

		case 2:
			return static_cast<uint32_t>(m_normals.size());

		default:
			return 0;
		}
	}

	uint32_t Model::Importer::AddVertex(void)
	{
		Vertex		newVertex(m_positions[m_CurrentPosition]);
		uint32_t	newIndex = static_cast<uint32_t>(m_currentModel->m_vertices.size());

		if (m_normals.size())
			newVertex.Normal() = m_normals[m_CurrentNormal];

		if (m_texCoords.size())
			newVertex.TextureCoords() = m_texCoords[m_CurrentTextureCoords];

		m_currentModel->m_vertices.push_back(newVertex);
		return newIndex;
	}

	uint32_t& Model::Importer::operator[](uint32_t index)
	{
		switch (index)
		{
		case 0:
			return m_CurrentPosition;

		case 1:
			return m_CurrentTextureCoords;

		case 2:
			return m_CurrentNormal;

		default: throw std::logic_error("Index out of range");
		}
	}



	Model::Importer::Importer(const std::filesystem::path& path)
		: m_file(path)
	{
	}

	Model* Model::Importer::LoadModel(void)
	{
		std::stringstream	objBuffer;


		if (!FileToBuffer(m_file, objBuffer))
			return nullptr;

		std::string			characters;

		objBuffer >> characters;
		m_root = m_currentModel = new Model();

		while (!objBuffer.eof())
		{
			switch (characters[0])
			{
			case 'v':
				PositionState(characters, objBuffer);
				break;

			case 'f':
				FaceState(characters, objBuffer);
				break;

			default:
				objBuffer >> characters;
				break;
			}
		}

		return m_root;
	}

	auto& Model::Importer::File()
	{
		return m_file;
	}
}