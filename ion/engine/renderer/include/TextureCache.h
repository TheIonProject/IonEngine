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