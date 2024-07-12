
#pragma once

#include <fstream>
#include <string>
#include <iostream>

#include "IonDebug.hpp"

#include "Shader.h"

namespace ion
{
	Shader::Shader(void)
		: m_vertexID(0), m_fragmentID(0)
	{
		m_id = glCreateProgram();
	}


	Shader::Shader(const std::filesystem::path& vertexShader, const std::filesystem::path& fragmentShader)
	{
		m_id = glCreateProgram();

		AddVertexShader(vertexShader);
		AddFragmentShader(fragmentShader);

		Link();
	}

	Shader::~Shader(void)
	{
		Delete();
	}


	bool Shader::ReadShaderString(const std::string& source, GLenum type)
	{
		return CompileSource(source.c_str(), type);
	}


	bool Shader::ReadShaderFile(const std::filesystem::path& file, GLenum type)
	{
		std::ifstream	shaderFile(file, std::ios::in | std::ios::binary);

		if (!shaderFile)
		{
			std::string	error("Unable to open file: ");

			error += file.string();

			ION_LOG_ERROR(error);
		}

		shaderFile.seekg(0, std::ios::end);

		int32_t			size = static_cast<int32_t>(shaderFile.tellg());
		char*			shaderSource = new char[size + sizeof(char)];

		shaderFile.seekg( std::ios::beg);
		shaderFile.read(shaderSource, size);

		shaderSource[size] = '\0';

		bool status = CompileSource(shaderSource, type);

		shaderFile.close();

		delete[] shaderSource;

		return status;
	}

	bool Shader::AddVertexShader(const std::filesystem::path& file)
	{
		return ReadShaderFile(file, GL_VERTEX_SHADER);
	}

	bool Shader::AddFragmentShader(const std::filesystem::path& file)
	{
		return ReadShaderFile(file, GL_FRAGMENT_SHADER);
	}

	bool Shader::Link(void)
	{
		glAttachShader(m_id, m_vertexID);
		glAttachShader(m_id, m_fragmentID);

		int32_t success;

		glLinkProgram(m_id);
		glGetProgramiv(m_id, GL_LINK_STATUS, &success);

		if (success)
			return true;

		char				infoLog[512];
		std::string			errorMessage("Shader program linking failed!");

		glGetProgramInfoLog(m_id, 512, NULL, infoLog);
		errorMessage += infoLog;

		ION_LOG_ERROR(errorMessage);

		return false;
	}

	void Shader::Delete(void)
	{
		if (m_vertexID)
			glDeleteShader(m_vertexID);
		if (m_fragmentID)
			glDeleteShader(m_fragmentID);

		glDeleteProgram(m_id);
	}


	void Shader::Use(void)
	{
		glUseProgram(m_id);
	}


	bool Shader::CompileSource(const char* shaderSource, GLenum type)
	{
		int32_t		success;
		uint32_t	shaderID = glCreateShader(type);

		if (type == GL_VERTEX_SHADER)
			m_vertexID = shaderID;
		else
			m_fragmentID = shaderID;

		glShaderSource(shaderID, 1, &shaderSource, NULL);
		glCompileShader(shaderID);
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

		if (success)
			return true;

		char				infoLog[512];
		std::stringstream	errorMessage;

		glGetShaderInfoLog(shaderID, 512, NULL, infoLog);


		errorMessage << "Shader compilation error!\n" <<
		TranslateShaderType(type) << ": " << infoLog;

		ION_LOG_ERROR(errorMessage.str());

		return false;
	}

	const char* Shader::TranslateShaderType(GLenum type)
	{
		switch (type)
		{
		case GL_VERTEX_SHADER: return "Vertex shader";
		case GL_FRAGMENT_SHADER: return "Fragment shader";
		case GL_GEOMETRY_SHADER: return "Geometry shader";
		}


		return "Unknown shader type";
	}
}