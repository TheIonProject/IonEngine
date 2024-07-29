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