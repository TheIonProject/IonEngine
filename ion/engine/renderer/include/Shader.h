#pragma once

#include <string>
#include <filesystem>

#include <glad/glad.h>

namespace ion
{
	class Shader
	{
	public:


			Shader(void);
			Shader(const std::filesystem::path& vertexShader,
				   const std::filesystem::path& fragmentShader);
			~Shader(void);

	bool	ReadShaderString(const std::string& source, GLenum type);
	bool	ReadShaderFile(const std::filesystem::path& file, GLenum type);

	bool	AddVertexShader(const std::filesystem::path& file);
	bool	AddFragmentShader(const std::filesystem::path& file);

	bool	Link(void);
	void	Delete(void);

	void	Use(void);

	private:

		bool		CompileSource(const char* shaderSource, GLenum type);
		const char* TranslateShaderType(GLenum type);

		uint32_t	m_id;
		uint32_t	m_vertexID;
		uint32_t	m_fragmentID;
	};





}