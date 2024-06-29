#include <exception>
#include <iostream>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>

#include "Application.h"

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
	//glfwWindowHint(GLFW_DECORATED, GLFW_FALSE); // TODO: re-add after adding UI
	glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Get monitor values for screen size & refresh rate
	const GLFWvidmode* vidMode = glfwGetVideoMode((GLFWmonitor*)glfwGetPrimaryMonitor());
	m_windowWidth = vidMode->width;
	m_windowHeight = vidMode->height;
	
	// Initialize window pointer
	m_windowPtr = glfwCreateWindow(m_windowWidth, m_windowHeight, "IonEngine", NULL, NULL);

	// Check window pointer is not null
	if (!m_windowPtr)
		throw std::exception("Window ptr is null");

	// Set context
	glfwMakeContextCurrent(m_windowPtr);
	glfwSetFramebufferSizeCallback(m_windowPtr, FrameBufferCallback);

	// Check glad init successfully
	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
		throw std::exception("GLAD init failed");

	InitImGui();

	// Initialize frame buffer
	m_frameBuffer = ion::FrameBuffer(
		static_cast<float>(m_windowWidth),
		static_cast<float>(m_windowHeight)
	);
}

void ion::Application::InitImGui(void)
{
	// Initialize ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	ImGui::StyleColorsDark(); // TODO: replace with own theme
	ImGui_ImplGlfw_InitForOpenGL(m_windowPtr, true);
	ImGui_ImplOpenGL3_Init("#version 450");
}

void ion::Application::UpdateApplication(void)
{
	ProcessInput(m_windowPtr);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // TODO: change to vector4
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui::NewFrame();
	ImGui::DockSpaceOverViewport();

	m_frameBuffer.Bind();
	m_frameBuffer.UnBind();
	ImGui::Begin("Scene");
	{
		ImGui::BeginChild("Render");

		ImVec2 contentRegion = ImGui::GetContentRegionAvail();
		float width = contentRegion.x;
		float height = contentRegion.y;
		
		ImGui::Text("test");
		//ImGui::Image(
		//	(ImTextureID) m_frameBuffer.GetFrameTexture(),
		//	contentRegion,
		//	ImVec2(0, 1),
		//	ImVec2(1, 0)
		//);
	}
	ImGui::EndChild();
	ImGui::End();

	
	ImGui::EndFrame();

	ImGui::Render();



	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	GLFWwindow* backup_current_context = glfwGetCurrentContext();
	ImGui::UpdatePlatformWindows();
	ImGui::RenderPlatformWindowsDefault();
	glfwMakeContextCurrent(backup_current_context);
	glfwSwapBuffers(m_windowPtr);
	glfwPollEvents();
}

void ion::FrameBufferCallback(GLFWwindow* windowPtr, int width, int height)
{
	(void) windowPtr;

	glViewport(0, 0, width, height);
}

void ion::ProcessInput(GLFWwindow* windowPtr)
{
	// TODO: remove, keybind just for debugging
	if (glfwGetKey(windowPtr, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(windowPtr, true);
}
