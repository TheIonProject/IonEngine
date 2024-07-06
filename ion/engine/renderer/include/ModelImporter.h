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

		bool			LoadModel(const std::filesystem::path& path);

		Model*&			CurrentModel();

	private:

		bool			FileToBuffer
		(const std::filesystem::path& path, std::stringstream& buffer);

		void			PositionState(std::string& string, std::stringstream& objBuffer);
		void			NormalState(std::string& string, std::stringstream& objBuffer);
		void			TextureCoordState(std::string& string, std::stringstream& objBuffer);

		void			FaceState(std::string& line, std::stringstream& objBuffer);
		void			AddFaceIndices(const std::vector<uint32_t>& vertexIndices);

		void			ProcessVertexIndices(const std::string& indexString);
		int32_t			NegativeToPositive(uint32_t index);

		uint32_t		AddVertex(void);

		uint32_t&		operator[](uint32_t index);

		VertexMap		m_uniqueVertices;

		Vec3Array		m_positions;
		Vec3Array		m_normals;
		Vec2Array		m_texCoords;

		Model*			m_currentModel = nullptr;


		uint32_t		m_CurrentPosition = 0;
		uint32_t		m_CurrentTextureCoords = 0;
		uint32_t		m_CurrentNormal = 0;
	};
}