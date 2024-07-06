#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>

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

		void UpdateApplication(void);
	private:
		void InitApplication(void);
		void InitImGui(void);

		GLFWwindow* m_windowPtr;
		TextureCache m_textureCache; // TODO: debug remove, move to resource manager
		FrameBuffer m_frameBuffer;
		Viewport m_viewport;
		int m_windowWidth;
		int m_windowHeight;
	};

}
