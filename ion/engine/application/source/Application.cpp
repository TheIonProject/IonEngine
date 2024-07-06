#include <iostream>
#include <exception>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>

#include "Application.h"
#include "TitleBar.h"
#include "Testing.h"

ion::Application::Application(void)
{
	m_windowPtr = nullptr;
	m_windowHeight = 0;
	m_windowWidth = 0;

	InitApplication();
}

ion::Application::~Application(void)
{
	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();

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

	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(m_windowPtr, &bufferWidth, &bufferHeight);
	glfwMakeContextCurrent(m_windowPtr);

	// Check glad init successfully
	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
		throw std::exception("GLAD init failed");

	glViewport(0, 0, bufferWidth, bufferHeight);
	create_triangle(); // Testing triangle
	create_shaders(); // Test shader


	// Initialize frame buffer
	m_frameBuffer.InitFrameBuffer();

	// Initialize ImGui
	InitImGui();

	m_viewport.SetViewportMode(ViewportMode::HD_RATIO);
}

void ion::Application::InitImGui(void)
{
	// Initialize ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void) io;
	io.ConfigWindowsMoveFromTitleBarOnly = true;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	ImGui::StyleColorsDark(); // TODO: replace with own theme
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}
	ImGui_ImplGlfw_InitForOpenGL(m_windowPtr, true);
	ImGui_ImplOpenGL3_Init("#version 450");
}

void ion::Application::UpdateApplication(void)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	ImGui::NewFrame();
	ImGui::DockSpaceOverViewport();

	MainMenuBar();
	m_viewport.UpdateViewport(m_frameBuffer);
	ImGui::ShowMetricsWindow();

	ImGui::Render();

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}

	glfwSwapBuffers(m_windowPtr);
	glfwPollEvents();
}
