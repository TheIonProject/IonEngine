/*
*	Testing File
*
*	This file is temporary and only used for testing other features
*	in the engine. Therefore, this file should be removed later.
*/

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

GLuint g_VAO;
GLuint g_VBO;
GLuint g_shader;

const char* vertex_shader_code = R"*(
	#version 450
	
	layout (location = 0) in vec3 pos;
	
	void main()
	{
		gl_Position = vec4(0.9*pos.x, 0.9*pos.y, 0.5*pos.z, 1.0);
	}
)*";

const char* fragment_shader_code = R"*(
	#version 450
	
	out vec4 color;
	
	void main()
	{
		color = vec4(0.0, 1.0, 0.0, 1.0);
	}
)*";


void create_triangle()
{
	GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &g_VAO);
	glBindVertexArray(g_VAO);

	glGenBuffers(1, &g_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void add_shader(GLuint program, const char* shader_code, GLenum type)
{
	GLuint current_shader = glCreateShader(type);

	const GLchar* code = shader_code;
	GLint code_length = static_cast<GLint>(strlen(shader_code));

	glShaderSource(current_shader, 1, &code, &code_length);
	glCompileShader(current_shader);

	GLint result = 0;
	GLchar log[1024] = {0};

	glGetShaderiv(current_shader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(current_shader, sizeof(log), NULL, log);
		std::printf("Error compiling %d shader: %s\n", type, log);
		return;
	}

	glAttachShader(program, current_shader);
}

void create_shaders()
{
	g_shader = glCreateProgram();
	if (!g_shader)
	{
		std::cout << "Error creating shader program!\n";
		exit(1);
	}

	add_shader(g_shader, vertex_shader_code, GL_VERTEX_SHADER);
	add_shader(g_shader, fragment_shader_code, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar log[1024] = {0};

	glLinkProgram(g_shader);
	glGetProgramiv(g_shader, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(g_shader, sizeof(log), NULL, log);
		std::printf("Error linking program: %s\n", log);
		return;
	}

	glValidateProgram(g_shader);
	glGetProgramiv(g_shader, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(g_shader, sizeof(log), NULL, log);
		std::printf("Error validating program: %s\n", log);
		return;
	}
}