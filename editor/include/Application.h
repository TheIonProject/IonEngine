/*

 _____                               _
|_   _|                             (_)
  | |  ___  _ __     ___ _ __   __ _ _ _ __   ___
  | | / _ \| '_ \   / _ \ '_ \ / _` | | '_ \ / _ \
 _| || (_) | | | | |  __/ | | | (_| | | | | |  __/
 \___/\___/|_| |_|  \___|_| |_|\__, |_|_| |_|\___|
								__/ |
							   |___/


NAME: Application.h

DESCTIPTION: Application class to handle OpenGL window & UI windows

AUTHOR: @MLev29 on GitHub


*/

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Viewport.h"
#include "TextureCache.h"

namespace ion
{
	class Application
	{
	public:
		Application(void);

		~Application(void);

		GLFWwindow* GetWindowPtr(void) const noexcept;
		GLFWwindow*& GetWindowPtr(void);

		void UpdateApplication(float deltaTime);

		static void StaticResizeWindowCallback(GLFWwindow* windowPtr, int width, int height);

		void ResizeWindowCallback(GLFWwindow* windowPtr, int width, int height);
	private:
		void InitApplication(void);
		void InitImGui(void);

		GLFWwindow* m_windowPtr;
		//TextureCache m_textureCache; // TODO: debug remove, move to resource manager
		//Viewport m_viewport;
		int m_windowWidth;
		int m_windowHeight;
	};
}
