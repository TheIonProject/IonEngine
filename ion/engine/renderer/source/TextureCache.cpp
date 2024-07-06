#include <iostream>
#include "TextureCache.h"
#include "TextureLoader.h"

#define DEBUG_TEXTURE_CACHE 0

ion::Texture ion::TextureCache::AddTexture(std::string textureFileName)
{
	// Get relative texture path
	std::string filePath = std::string(TEXTURE_PATH) + textureFileName;

	// Look up texture
	auto lookupTexture = m_textureMap.find(filePath);

	// Check texture is not already inside texture map
	if (lookupTexture == m_textureMap.end())
	{
#if DEBUG_TEXTURE_CACHE == 1
		std::printf("Texture not found in map\n");
#endif

		// Load new unique texture
		Texture appendTexture = TextureLoader::LoadTexture(filePath);

		// Add new texture to map
		m_textureMap.insert(std::make_pair(filePath, appendTexture));

		// Print success message
		std::cout << "Texture added to texture cache successfully\n";

		return appendTexture;
	}
	else
	{
#if DEBUG_TEXTURE_CACHE == 1
		std::printf("Failed to add texture to texture map.\nReason: Texture is already in the texture map\n");
#endif
	}

	return lookupTexture->second;
}

void ion::TextureCache::BindTexture(std::string textureFileName)
{
	std::string filePath = std::string(TEXTURE_PATH) + textureFileName;

	auto getTexture = m_textureMap.find(filePath);

	// Check texture exists
	if (getTexture == m_textureMap.end())
	{
#if DEBUG_TEXTURE_CACHE == 1
		std::printf("Texture does not exist\n");
		__debugbreak();
#endif
		return;
	}

	glBindTexture(GL_TEXTURE_2D, getTexture->second.m_id);
}

//ion::Texture ion::TextureCache::GetTexture(std::string textureName)
//{
//	std::string filePath = std::string(TEXTURE_PATH) + textureName;
//	auto getTexture = m_textureMap.find(filePath);
//
//	// Check texture exists
//	if (getTexture == m_textureMap.end())
//	{
//		std::printf("Texture does not exist\n");
//
//		return ;
//	}
//
//	return getTexture->second;
//}

ion::Texture ion::TextureCache::GetTexture(std::string textureName) const noexcept
{
	std::string filePath = std::string(TEXTURE_PATH) + textureName;

	auto getTexture = m_textureMap.find(filePath);

	// Check texture exists
	if (getTexture == m_textureMap.end())
	{
		std::printf("Texture does not exist");
#if DEBUG_TEXTURE_CACHE == 1
		__debugbreak();
#else
		return Texture();
#endif
	}

	return getTexture->second;
}
