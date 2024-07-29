/*

 _____                               _
|_   _|                             (_)
  | |  ___  _ __     ___ _ __   __ _ _ _ __   ___
  | | / _ \| '_ \   / _ \ '_ \ / _` | | '_ \ / _ \
 _| || (_) | | | | |  __/ | | | (_| | | | | |  __/
 \___/\___/|_| |_|  \___|_| |_|\__, |_|_| |_|\___|
								__/ |
							   |___/


NAME: Application.cpp

DESCTIPTION: Logic for application class. Application class handles initialization & updates
of dependencies such as GLFW, Glad & ImGui.

AUTHOR: @MLev29 on GitHub


*/

#include <iostream>
#include <exception>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>

#include "Application.h"
#include "TitleBar.h"
#include "Testing.h"
#include "Theme.hpp"

ion::Application::Application(void)
{
	// Initialize application variables
	m_windowPtr = nullptr;
	m_windowWidth = 800;
	m_windowHeight = 600;
	//m_viewport = ion::Viewport(ion::ViewportMode::HD_RATIO);

	InitApplication();
}

ion::Application::~Application(void)
{
	// Free memory to prevent memory leaks
	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(m_windowPtr);
	glfwTerminate();
}

GLFWwindow* ion::Application::GetWindowPtr(void) const noexcept
{
	return m_windowPtr;
}

GLFWwindow*& ion::Application::GetWindowPtr(void)
{
	return m_windowPtr;
}

void ion::Application::InitApplication(void)
{
	// Initialize GLFW
	if (glfwInit() == GLFW_FALSE)
		throw std::exception("GLFW init failed");

	// Set window hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_FALSE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	//glfwWindowHint(GLFW_DECORATED, GLFW_FALSE); // TODO: re-add after adding UI (removes top menu bar)
	glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Get monitor values for screen size & refresh rate
	const GLFWvidmode* vidMode = glfwGetVideoMode((GLFWmonitor*) glfwGetPrimaryMonitor());
	m_windowWidth = vidMode->width;
	m_windowHeight = vidMode->height;

	// Initialize window pointer
	m_windowPtr = glfwCreateWindow(m_windowWidth, m_windowHeight, "IonEngine", NULL, NULL);

	// Check window pointer is not null
	if (!m_windowPtr)
		throw std::exception("Window ptr is null");

	glfwSetWindowUserPointer(m_windowPtr, this);
	glfwSetWindowSizeCallback(m_windowPtr, StaticResizeWindowCallback);

	glfwMakeContextCurrent(m_windowPtr);

	// Check glad init successfully
	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
		throw std::exception("GLAD init failed");

	// Enable depth buffer
	glEnable(GL_DEPTH_TEST);

	// HACK: Create shader currently being used to for 3D object in viewport
	// This would need to be changed for a more permanent solution
	create_shaders(); // Test shader

	// Initialize ImGui
	InitImGui();

	// Initialize viewport
	//m_viewport.InitViewport();

	// Initialize frame buffer
	//m_viewport.m_frameBuffer->InitFrameBuffer();

	// Do not remove this line or viewport goes kaputt on init.
	glViewport(0, 0, 800, 600);
}

void ion::Application::InitImGui(void)
{
	// Initialize ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	// Set flags
	ImGuiIO& io = ImGui::GetIO(); (void) io;
	io.ConfigWindowsMoveFromTitleBarOnly = true;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	// Set editor theme
	UITheme();

	// More ImGui initializing stuff...
	ImGui_ImplGlfw_InitForOpenGL(m_windowPtr, true);
	ImGui_ImplOpenGL3_Init("#version 450");
}

void ion::Application::UpdateApplication(float /*deltaTime*/)
{
	// Check scene view is an active window
	//if (m_viewport.GetWindowActive())
	//{
	//	// Process mouse & keyboard input for scene view
	//	glfwSetInputMode(m_windowPtr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//	//m_viewport.m_camera->CameraInput(m_windowPtr, deltaTime);
	//	//m_viewport.m_camera->MouseMotion(m_viewport.GetMousePosition(), deltaTime);
	//}
	//else
	//{
	//	//m_viewport.m_camera->SetLastCursorPos(m_viewport.GetMousePosition());
	//	glfwSetInputMode(m_windowPtr, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	//}

	//glBindFramebuffer(GL_FRAMEBUFFER, m_viewport.m_frameBuffer->GetFrameBuffer());
	//glEnable(GL_DEPTH_TEST);

	//// Clear background & color buffer
	//glClearColor(0.0f, 0.2f, 0.2f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//// Create new frame for UI
	//ImGui_ImplOpenGL3_NewFrame();
	//ImGui_ImplGlfw_NewFrame();
	//ImGui::NewFrame();

	//// Enable docking for UI windows
	//ImGui::DockSpaceOverViewport();
	//
	//// UI
	//MainMenuBar();
	//m_viewport.UpdateViewport(m_windowPtr, *m_viewport.m_frameBuffer);
	//ImGui::ShowMetricsWindow(); // TODO: debug remove
	//
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//glDisable(GL_DEPTH_TEST);

	//// Render UI
	//ImGui::Render();
	//ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	//// Viewport / docking stuff...
	//if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	//{
	//	GLFWwindow* backupContext = glfwGetCurrentContext();
	//	ImGui::UpdatePlatformWindows();
	//	ImGui::RenderPlatformWindowsDefault();
	//	glfwMakeContextCurrent(backupContext);
	//}

	//// Swap front & back buffer
	//glfwSwapBuffers(m_windowPtr);
	//glfwPollEvents();
}

void ion::Application::StaticResizeWindowCallback(GLFWwindow* windowPtr, int width, int height)
{
	// Function to call resize window function, used for frame buffer size
	Application* applicationPtr = static_cast<Application*>(glfwGetWindowUserPointer(windowPtr));

	applicationPtr->ResizeWindowCallback(windowPtr, width, height);
}

void ion::Application::ResizeWindowCallback(GLFWwindow* windowPtr, int width, int height)
{
	// Function to prevent viewport bugging out :'C
	(void) windowPtr;

	glViewport(0, 0, width, height);

	//m_viewport.m_frameBuffer->RescaleFrameBuffer(width, height);
}
