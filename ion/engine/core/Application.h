#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>

namespace Ion
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

		GLFWwindow* m_windowPtr;
		unsigned int m_windowWidth;
		unsigned int m_windowHeight;

	};

	void FrameBufferCallback(GLFWwindow* windowPtr, int width, int height);
	void ProcessInput(GLFWwindow* windowPtr);
}
