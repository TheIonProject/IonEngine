#include <iostream>
#include <fstream>
#include <vector>
#include <list>

#include "IonDebug.hpp"
#include "IonUtils.hpp"

#include "ModelImporter.h"

namespace ion
{
	Model::WavefrontImporter::WavefrontImporter(Model* model)
		: m_currentModel(model)
	{
	}



	bool Model::WavefrontImporter::LoadModel(const std::filesystem::path& path)
	{
		if (!m_currentModel)
			return false;

		std::stringstream	objBuffer;

		// Write file into stringstream
		if (!FileToBuffer(path, objBuffer))
			return false;

		// Whitespace separated line portion
		std::string			characters;

		objBuffer >> characters;

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

		return true;
	}



	bool Model::WavefrontImporter::FileToBuffer(const std::filesystem::path& path, std::stringstream& buffer)
	{
		std::ifstream		fileStream(path, std::ios::in);

		if (!fileStream)
		{
			std::stringstream	message("Unable to open ");

			message << path.string() << ".\n";

			ION_LOG_ERROR(message.str());

			return false;
		}

		// Extract entire file into stringstream
		buffer << fileStream.rdbuf();

		return true;
	}


	void Model::WavefrontImporter::PositionState(std::string& string, std::stringstream& objBuffer)
	{
		if (string.size() > 1)
		{
			switch (string[1])
			{

			// string = vt
			case 't':
				TextureCoordState(string, objBuffer);
				return;

			// string = vn
			case 'n':
				NormalState(string, objBuffer);
				return;

			// string = v
			default: break;
			}
		}

		float				x, y, z;
		std::stringstream	line;

		objBuffer >> string;

		// Write numbers into vector
		while (std::string("+-0123456789").find(string[0]) != std::string::npos)
		{
			x = static_cast<float>(atof(string.c_str()));

			objBuffer >> y >> z >> string;

			m_positions.emplace_back(x, y, z);

		}
	}



	void Model::WavefrontImporter::NormalState(std::string& string, std::stringstream& objBuffer)
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

	void Model::WavefrontImporter::TextureCoordState(std::string& string, std::stringstream& objBuffer)
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

	void Model::WavefrontImporter::FaceState(std::string& line, std::stringstream& objBuffer)
	{
		/*
			Unique vertices are stored in an unordered map
			with their index string (e.g. 7/5/3) as a key,
			and their position in the vertex buffer as value
		*/



		std::vector<uint32_t>		vertexIndices;
		std::string					indexString;
		uint8_t						iteration = 0, loopSafety = 100;

		objBuffer >> indexString;

		// Read all face strings on this line
		while (true)
		{
			// Vertex already exists
			if (m_uniqueVertices.contains(indexString))
			{
				uint32_t		existingIndex = m_uniqueVertices[indexString];

				vertexIndices.push_back(existingIndex);
			}

			// Vertex is new
			else
			{
				// Get indices from string
				ProcessVertexIndices(indexString);

				// Add to vertex buffer and ger new index
				uint32_t		newVertex = AddVertex();

				// Add to index buffer and create new entry in map
				vertexIndices.push_back(newVertex);
				m_uniqueVertices[indexString] = newVertex;

			}

			indexString = std::string();
			objBuffer >> indexString;

			// No longer a valid face line
			if (std::string("+-0123456789").find(indexString[0]) == std::string::npos)
				break;

			// Potentially infinite loop, no face should be this long
			if(++iteration > loopSafety)
				throw std::exception("Invalid face");
		}

		AddFaceIndices(vertexIndices);

		// Leave state before walking pointer back if finished reading file
		if (objBuffer.eof())
			return;

		// Put back last string in buffer
		objBuffer.seekg(objBuffer.tellg() - static_cast<long long>(indexString.size()));

		// line will be read by caller function to decide which state
		// to enter next
		objBuffer >> line;


	}


	void Model::WavefrontImporter::ProcessVertexIndices(const std::string& faceString)
	{
		std::string		index;

		uint32_t		vertexAttribute = 0;
		size_t			character = 0;

		while (character < faceString.size())
		{
			// Divisor token found
			if (faceString[character] == '/')
			{
				int32_t convertedIndex = atoi(index.c_str());

				// Adjust negative index
				// and avoid subtracting from 0
				if (convertedIndex < 1)
					convertedIndex += NegativeToPositive(vertexAttribute);

				// Wavefront indices start from 1 so adjust value
				// to make it start from 0
				else
					convertedIndex -= 1;

				// Save face index
				(*this)[vertexAttribute] = convertedIndex;

				// Reset string to start reading next one
				index = std::string();

				++character;
				++vertexAttribute;

				continue;
			}

			index += faceString[character];
			++character;
		}

	}



	void Model::WavefrontImporter::AddFaceIndices(const std::vector<uint32_t>& vertexIndices)
	{
		switch (vertexIndices.size())
		{
		case 0: break;
		case 1:
		case 2:
			throw std::exception("Invalid face in model");

		case 3:

			// Append triangle to index buffer
			m_currentModel->m_indices += vertexIndices;
			break;

		case 4:

			// Add 6 indices to make a quad
			m_currentModel->m_indices += vertexIndices;
			m_currentModel->m_indices.push_back(vertexIndices[2]);
			m_currentModel->m_indices.push_back(vertexIndices[0]);
			break;

		default:
			// Organize vertices in a fan
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



	int32_t Model::WavefrontImporter::NegativeToPositive(uint32_t index)
	{
		// Get vector size to turn relative (negative) index into positive
		// index starting from 0
		switch (index)
		{
		case 0:
			return static_cast<int32_t>(m_positions.size());

		case 1:
			return static_cast<int32_t>(m_texCoords.size());

		case 2:
			return static_cast<int32_t>(m_normals.size());

		default:
			return 0;
		}
	}


	uint32_t Model::WavefrontImporter::AddVertex(void)
	{
		// Create vertex from position
		Vertex		newVertex(m_positions[m_CurrentPosition]);
		uint32_t	newIndex = static_cast<uint32_t>(m_currentModel->m_vertices.size());

		// Add optional attributes

		if (m_normals.size())
			newVertex.Normal() = m_normals[m_CurrentNormal];

		if (m_texCoords.size())
			newVertex.TextureCoords() = m_texCoords[m_CurrentTextureCoords];

		m_currentModel->m_vertices.push_back(newVertex);
		return newIndex;
	}



	uint32_t& Model::WavefrontImporter::operator[](uint32_t index)
	{
		// Return vector index depending on the one we want

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

}