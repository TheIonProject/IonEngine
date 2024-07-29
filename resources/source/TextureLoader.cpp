/*

 _____                               _
|_   _|                             (_)
  | |  ___  _ __     ___ _ __   __ _ _ _ __   ___
  | | / _ \| '_ \   / _ \ '_ \ / _` | | '_ \ / _ \
 _| || (_) | | | | |  __/ | | | (_| | | | | |  __/
 \___/\___/|_| |_|  \___|_| |_|\__, |_|_| |_|\___|
								__/ |
							   |___/


NAME: TextureLoader.cpp

DESCTIPTION: Backend for initializing textures

AUTHOR: @MLev29 on GitHub


*/

#define STB_IMAGE_IMPLEMENTATION 
#include <iostream>

#include <glad/glad.h>
#include <stb/stb_image.h>

#include "TextureLoader.h"

ion::Texture ion::TextureLoader::LoadTexture(std::string const filePath)
{
	Texture appendTexture;
	int nrChannels;

	glGenTextures(1, &appendTexture.m_id);
	glBindTexture(GL_TEXTURE_2D, appendTexture.m_id);

	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load image, create texture and generate mipmaps
	unsigned char* data = stbi_load(filePath.c_str(), &appendTexture.m_width, &appendTexture.m_height, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, appendTexture.m_width, appendTexture.m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture: " << filePath.c_str() << '\n';

	stbi_image_free(data);

	return appendTexture;
}

void ion::TextureLoader::LogError(ErrorType errorType)
{
	// TODO: implement function in code
	switch (errorType)
	{
	case ion::TextureLoader::INVALID_FILE_TYPE:
		std::printf("File type not supported. To see all supported file extensions check the stb_image documentation.\n");
		break;
	case ion::TextureLoader::FILE_NOT_FOUND:
		std::printf("File could not be found. File either does not exist or is in the wrong directory\n");
		break;
	case ion::TextureLoader::LOAD_FAILED:
		std::printf("Loading texture failed\n");
		break;
	default:
		break;
	}
}
