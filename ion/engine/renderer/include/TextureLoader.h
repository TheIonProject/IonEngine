#pragma once

#include <string>

#include "TextureCache.h"

#define TEXTURE_PATH "../../../assets/textures/"

namespace ion
{
	class TextureLoader
	{
	public:
		static Texture LoadTexture(std::string const filePath);
	private:
		enum ErrorType
		{
			INVALID_FILE_TYPE,
			FILE_NOT_FOUND,
			LOAD_FAILED
		};

		void LogError(ErrorType errorType);
	};
}