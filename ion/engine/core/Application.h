#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>

#include "FrameBuffer.h"

namespace ion
{
	static class Application
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

		void UpdateViewport(void);

		GLFWwindow* m_windowPtr;
		int m_windowWidth;
		int m_windowHeight;
		FrameBuffer m_frameBuffer;
	};

}
