#pragma once

#include <string>
#include <filesystem>

#include <glad/glad.h>

#include "math/Matrix4.hpp"

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

	void	Use(void)															const;


	void	SetUniform(const char* name, int value)								const;
	void	SetUniform(const char* name, float value)							const;

	void	SetUniform(const char* name, int count, float* values)				const;
	void	SetUniform(const char* name, int count, int* values)				const;

	void	SetUniform(const char* name, const math::Vector3f& values)			const;
	void	SetUniform(const char* name, const math::Vector4f& values)			const;

	void	SetUniform(const char* name, float val1, float val2, float val3)	const;
	void	SetUniform(const char* name, int val1, int val2, int val3)			const;

	void	SetUniform(const char* name, const math::Matrix3f& matrix)			const;
	void    SetUniform(const char* name, const math::Matrix4f& matrix)			const;

	private:

		bool		CompileSource(const char* shaderSource, GLenum type);
		const char* TranslateShaderType(GLenum type);

		uint32_t	m_id;
		uint32_t	m_vertexID;
		uint32_t	m_fragmentID;
	};





}