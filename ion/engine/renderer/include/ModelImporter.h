#pragma once

#include <unordered_map>

#include "Model.h"


namespace ion
{
	class Model::Importer
	{
	private:

		using Vec2Array = std::vector<math::Vector2f>;
		using Vec3Array = std::vector<math::Vector3f>;
		using VertexMap = std::unordered_map<const char*, int32_t>;

		using FileName = std::filesystem::path;

	public:

		Importer(void) = default;
		Importer(const std::filesystem::path& path);

		~Importer(void) = default;

		Model* LoadModel(void);

		// auto = std::filesystem::path
		auto& File();

	private:

		bool			FileToBuffer
		(const FileName& path, std::stringstream& buffer);


		void			PositionState(std::string& string, std::stringstream& objBuffer);
		void			NormalState(std::string& string, std::stringstream& objBuffer);
		void			TextureCoordState(std::string& string, std::stringstream& objBuffer);

		void			FaceState(std::string& line, std::stringstream& objBuffer);

		void			ProcessVertexIndices(const std::string& indexString);
		int32_t			NegativeToPositive(int32_t index);

		int32_t			AddVertex(void);

		int32_t&		operator[](int32_t index);


		VertexMap		m_uniqueVertices;
		FileName		m_file;

		Vec3Array		m_positions;
		Vec3Array		m_normals;
		Vec2Array		m_texCoords;

		Model*			m_root = nullptr;
		Model*			 m_currentModel = nullptr;


		int32_t			m_CurrentPosition = 0;
		int32_t			m_CurrentTextureCoords = 0;
		int32_t			m_CurrentNormal = 0;
	};
}