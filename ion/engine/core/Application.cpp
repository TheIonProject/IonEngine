#include <exception>
#include <iostream>

#include "Application.h"

Ion::Application::Application(void)
{
	m_windowPtr = nullptr;
	m_windowHeight = 0;
	m_windowWidth = 0;

	InitApplication();
}

Ion::Application::~Application(void)
{
	glfwTerminate();
}

GLFWwindow* Ion::Application::GetWindowPtr(void) const noexcept
{
	return m_windowPtr;
}

GLFWwindow*& Ion::Application::GetWindowPtr(void)
{
	return m_windowPtr;
}

void Ion::Application::InitApplication(void)
{
	// Initialize GLFW
	if (glfwInit() == GLFW_FALSE)
		throw std::exception("GLFW init failed");
	
	// Set window hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_FALSE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Get monitor values for screen size & refresh rate
	const GLFWvidmode* vidMode = glfwGetVideoMode((GLFWmonitor*)glfwGetPrimaryMonitor());
	m_windowWidth = vidMode->width;
	m_windowHeight = vidMode->height;
	
	// Initialize window pointer
	m_windowPtr = glfwCreateWindow(m_windowWidth, m_windowHeight, "IonEngine", NULL, NULL);
	
	// Set refresh rate
	glfwSetWindowMonitor(m_windowPtr, (GLFWmonitor*) glfwGetPrimaryMonitor(), 0, 0, m_windowWidth, m_windowHeight, vidMode->refreshRate);

	// Check window pointer is not null
	if (!m_windowPtr)
		throw std::exception("Window ptr is null");

	// Set context
	glfwMakeContextCurrent(m_windowPtr);
	glfwSetFramebufferSizeCallback(m_windowPtr, FrameBufferCallback);

	// Check glad init successfully
	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
		throw std::exception("GLAD init failed");
}

void Ion::Application::UpdateApplication(void)
{
	ProcessInput(m_windowPtr);

	glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // TODO: change to vector4
	glClear(GL_COLOR_BUFFER_BIT);

	glfwSwapBuffers(m_windowPtr);
	glfwPollEvents();
}

void Ion::FrameBufferCallback(GLFWwindow* windowPtr, int width, int height)
{
	(void) windowPtr;

	glViewport(0, 0, width, height);
}

void Ion::ProcessInput(GLFWwindow* windowPtr)
{
	// TODO: remove, keybind just for debugging
	if (glfwGetKey(windowPtr, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(windowPtr, true);
}
