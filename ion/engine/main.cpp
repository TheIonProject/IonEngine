#include <exception>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>


void FrameBufferCallback(GLFWwindow* windowPtr, int width, int height)
{
	glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow* windowPtr)
{
	if (glfwGetKey(windowPtr, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(windowPtr, true);
}

int main(void)
{
	int isGLFWInit = glfwInit();

	if (isGLFWInit == GLFW_FALSE)
		throw std::exception("GLFW init failed");
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_FALSE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	int width = glfwGetVideoMode(monitor)->width;
	int height = glfwGetVideoMode(monitor)->height;

	GLFWwindow* windowPtr = glfwCreateWindow(width, height, "IonEngine", NULL, NULL);
	glfwSetWindowMonitor(windowPtr, monitor, 0, 0, width, height, glfwGetVideoMode(monitor)->refreshRate);
	

	if (!windowPtr)
		throw std::exception("Window ptr is null");

	glfwMakeContextCurrent(windowPtr);
	glfwSetFramebufferSizeCallback(windowPtr, FrameBufferCallback);

	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
		throw std::exception("GLAD init failed");

	while (!glfwWindowShouldClose(windowPtr))
	{
		ProcessInput(windowPtr);

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(windowPtr);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}