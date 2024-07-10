/*

 _____                               _
|_   _|                             (_)
  | |  ___  _ __     ___ _ __   __ _ _ _ __   ___
  | | / _ \| '_ \   / _ \ '_ \ / _` | | '_ \ / _ \
 _| || (_) | | | | |  __/ | | | (_| | | | | |  __/
 \___/\___/|_| |_|  \___|_| |_|\__, |_|_| |_|\___|
								__/ |
							   |___/


NAME: TextureCache.h

DESCTIPTION: Initialize, store & get textures

AUTHOR: @MLev29 on GitHub


*/

#pragma once

#include <string>
#include <unordered_map>
#include <glad/glad.h>

namespace ion
{
	struct Texture
	{
		GLuint m_id = 0;
		int m_width = 0;
		int m_height = 0;
	};

	class TextureCache
	{
	public:
		TextureCache(void) = default;
		~TextureCache(void) = default;

		Texture AddTexture(std::string textureFileName);
		void BindTexture(std::string textureFileName);
		//Texture& GetTexture(std::string textureName);
		Texture GetTexture(std::string textureName) const noexcept;

	private:
		std::unordered_map<std::string, Texture> m_textureMap;
	};
}