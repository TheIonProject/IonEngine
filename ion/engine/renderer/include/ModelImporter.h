/*

 _____                               _
|_   _|                             (_)
  | |  ___  _ __     ___ _ __   __ _ _ _ __   ___
  | | / _ \| '_ \   / _ \ '_ \ / _` | | '_ \ / _ \
 _| || (_) | | | | |  __/ | | | (_| | | | | |  __/
 \___/\___/|_| |_|  \___|_| |_|\__, |_|_| |_|\___|
								__/ |
							   |___/


NAME: ModelImporter.h

DESCTIPTION: Importer classes for different file format

AUTHOR: Noah de Pischof | @torrra on GitHub


*/



#pragma once

#include <unordered_map>

#include "Model.h"


namespace ion
{
	class Model::WavefrontImporter final
	{
	private:

		using Vec2Array = std::vector<math::Vector2f>;
		using Vec3Array = std::vector<math::Vector3f>;
		using VertexMap = std::unordered_map<std::string, uint32_t>;

	public:

						WavefrontImporter(void) = default;
						WavefrontImporter(Model* model);
						~WavefrontImporter(void) = default;

		//	Load .obj file
		bool			LoadModel(const std::filesystem::path& path);

	private:

		// Copy .obj file into stream
		bool			FileToBuffer(const std::filesystem::path& path, std::stringstream& buffer);

		// Save position vector, or move on to vertex normal or texture coordinate states
		void			PositionState(std::string& string, std::stringstream& objBuffer);

		// Save vertex normal vector
		void			NormalState(std::string& string, std::stringstream& objBuffer);

		// Save texture coordinate vector
		void			TextureCoordState(std::string& string, std::stringstream& objBuffer);

		// Save face indices
		void			FaceState(std::string& line, std::stringstream& objBuffer);

		// Add indices in face line to model index vector
		void			AddFaceIndices(const std::vector<uint32_t>& vertexIndices);

		// Read face string and divide into integral indices
		void			ProcessVertexIndices(const std::string& indexString);

		// Adjust negative indices
		int32_t			NegativeToPositive(uint32_t index);

		// Add new vertex to vertex buffer
		uint32_t		AddVertex(void);

		uint32_t&		operator[](uint32_t index);



// ---- Data ----

		VertexMap		m_uniqueVertices;

		Vec3Array		m_positions;
		Vec3Array		m_normals;
		Vec2Array		m_texCoords;

		Model*			m_currentModel = nullptr;


// ---- Current vector indices ----

		uint32_t		m_CurrentPosition = 0;
		uint32_t		m_CurrentTextureCoords = 0;
		uint32_t		m_CurrentNormal = 0;
	};
}