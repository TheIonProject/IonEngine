/*

 _____                               _
|_   _|                             (_)
  | |  ___  _ __     ___ _ __   __ _ _ _ __   ___
  | | / _ \| '_ \   / _ \ '_ \ / _` | | '_ \ / _ \
 _| || (_) | | | | |  __/ | | | (_| | | | | |  __/
 \___/\___/|_| |_|  \___|_| |_|\__, |_|_| |_|\___|
								__/ |
							   |___/


NAME: Viewport.cpp

DESCTIPTION: Viewport class, made to handle scene view window

AUTHOR: @MLev29 on GitHub


*/

#include <iostream>
#include <exception>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>

#include "math/Matrix4.hpp"

#include "Viewport.h"
#include "Testing.h"
#include "Model.h"

#define DEBUG_VIEWPORT 0

ion::Viewport::Viewport(ViewportMode const viewportMode)
{
	m_frameBuffer = nullptr;
	m_camera = nullptr;
	m_currentMode = viewportMode;
	m_prevMode = m_currentMode;
	m_width = 0;
	m_height = 0;
	m_position = ImVec2(0.0f, 0.0f);
	m_isOpened = (viewportMode == ViewportMode::CUSTOM_RATIO);
	m_isWindowActive = false;
}

ion::Viewport::Viewport(Viewport const& viewport)
{
	m_frameBuffer = viewport.m_frameBuffer;
	m_camera = viewport.m_camera;
	m_currentMode = viewport.m_currentMode;
	m_prevMode = viewport.m_prevMode;
	m_width = viewport.m_width;
	m_height = viewport.m_height;
	m_vertexArray = viewport.m_vertexArray;
	m_isOpened = viewport.m_isOpened;
	m_isWindowActive = viewport.m_isWindowActive;
}

ion::Viewport::~Viewport(void)
{
	// Free memory to prevent memory leaks
	delete m_frameBuffer;
	delete m_camera;
	delete m_vertexArray;
}

ion::ViewportMode ion::Viewport::GetViewportMode(void) const noexcept
{
	return m_currentMode;
}

LibMath::Vector2f ion::Viewport::GetMousePosition(void) const noexcept
{
	ImVec2 cursorPos = ImGui::GetMousePos();

	return LibMath::Vector2f(cursorPos.x, cursorPos.y);
}

bool ion::Viewport::GetWindowActive(void) const noexcept
{
	return m_isWindowActive;
}

void ion::Viewport::SetViewportMode(ViewportMode const viewportMode)
{
	m_currentMode = viewportMode;
}

void ion::Viewport::InitViewport(void)
{
	// Initialize mesh
	Model model;
	model.ImportWavefront("../../../assets/models/cube.obj");
	
	// Initialize pointers
	m_frameBuffer = new ion::FrameBuffer();
	m_vertexArray = new ion::VertexArray(model);
	m_camera = new ion::Camera(math::Vector3f(0.0f, 1.0f, 3.0f), 1.0f);
}

void ion::Viewport::UpdateViewport(GLFWwindow* windowPtr, FrameBuffer& frameBuffer)
{
	(void) windowPtr;
	// Get viewport 
	ImVec2 region = ImGui::GetContentRegionAvail();

	glUseProgram(g_shader);
	
	// Camera matrix to make MVP matrix
	math::Matrix4f model(1.0f);
	math::Matrix4f view = m_camera->GetViewMatrix();
	math::Matrix4f projection = m_camera->GetPerspectiveMatrix(0.1f, 100.0f, 60.0f, region.x / region.y);

	glUniformMatrix4fv(glGetUniformLocation(g_shader, "model"), 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(g_shader, "view"), 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(g_shader, "projection"), 1, GL_FALSE, &projection[0][0]);

	// Model
	m_vertexArray->Draw();
	glBindVertexArray(0);

	m_camera->CameraUI();
	
	ImGui::Begin("Editor View", nullptr, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar);

	// Update if window is active	
	m_isWindowActive = ImGui::IsWindowFocused();

	OptionBarUI();
	SetViewportSize();
	ViewportPosition();

	uint64_t textureID = frameBuffer.GetFrameTexture();
	ImGui::Image(
		reinterpret_cast<void*>(textureID),
		ImVec2((float)m_width, (float)m_height),
		ImVec2(0, 1),
		ImVec2(1, 0)
	);

	ImGui::End();
}

void ion::Viewport::SetViewportSize(void)
{
	// Value obtained from dividing 1080 by 1920
	constexpr float hdAspectRatio = 0.5625f;
	ImVec2 windowSize = ImGui::GetContentRegionAvail();

	const int originalWidth = m_width;
	const int originalHeight = m_height;

	// Set viewport mode
	switch (m_currentMode)
	{
	case ViewportMode::HD_RATIO:
		m_width = (int) windowSize.x;
		m_height = (int) ((float) m_width * hdAspectRatio);
		break;
	case ViewportMode::FILL_WINDOW:
		m_width = (int) windowSize.x;
		m_height = (int) windowSize.y;
		break;
	case ViewportMode::CUSTOM_RATIO:
		CustomAspectModal(originalWidth, originalHeight);
		break;
	default:
		throw std::exception("Invalid viewport mode");
		break;
	}
}

void ion::Viewport::ViewportPosition(void)
{
	ImVec2 pos = ImGui::GetCursorScreenPos();
	ImVec2 regionSize = ImGui::GetContentRegionAvail();

	m_position.x = pos.x;
	// TODO: line below may be broken
	m_position.y = pos.y + (0.5f * (regionSize.y - m_height));
}

void ion::Viewport::OptionBarUI(void)
{
	const char* options[] =
	{
		"Free aspect",
		"16:9 HD",
		"Custom aspect"
	};

	constexpr int arraySize = IM_ARRAYSIZE(options);

	if (ImGui::BeginMenuBar())
	{
		const char* currentOption = options[(int) m_currentMode];

		if (ImGui::BeginCombo("Window aspect ratio", currentOption))
		{
			for (int i = 0; i < arraySize; ++i)
			{
				bool isSelected = (currentOption == options[i]);

				if (ImGui::Selectable(options[i], isSelected))
				{
#if DEBUG_VIEWPORT == 1
					std::printf("%s\n", options[i]);
#endif
					m_prevMode = static_cast<ViewportMode>(m_currentMode);
					currentOption = options[i];
					m_currentMode = static_cast<ViewportMode>(i);
					
					m_isOpened = (currentOption == options[2]);
				}

				if (isSelected)
				{
					ImGui::SetItemDefaultFocus();
				}				
			}

			ImGui::EndCombo();
		}

		ImGui::EndMenuBar();
	}
}

void ion::Viewport::CustomAspectModal(int const originalWidth, int const originalHeight)
{
	if (!m_isOpened)
		return;

	ImGuiIO& io = ImGui::GetIO();
	ImVec2 pos(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f);
	ImGui::SetNextWindowPos(pos, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
	ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove
		| ImGuiWindowFlags_NoDecoration
		| ImGuiWindowFlags_AlwaysAutoResize
		| ImGuiWindowFlags_NoSavedSettings
		| ImGuiWindowFlags_NoDocking;

	constexpr int minIncrement = 1;
	constexpr int maxIncrement = 10;
	
	if (ImGui::Begin("Custom Aspect Ratio", nullptr, flags))
	{
		// Title text
		ImGui::Text("Set viewport size (in pixels)");
		
		// Formatting
		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();

		// Input fields
		if (ImGui::InputInt("Width", &m_width, minIncrement, maxIncrement)) {}
		ImGui::Spacing();
		if (ImGui::InputInt("Height", &m_height, minIncrement, maxIncrement)) {}
		ImGui::Spacing();
		
#if DEBUG_VIEWPORT == 1
			std::printf("original size: (%d, %d)\nNew size: (%d, %d)\n", originalWidth, originalHeight, m_width, m_height);
#endif
#ifdef WIP_CANCEL_BUTTON
		// Cancel button
		if (ImGui::Button("Cancel", ImVec2(150, 0)))
		{
			// Reset screen size
			m_width = originalWidth;
			m_height = originalHeight;

			// Close popup
			m_isOpened = false;
			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
#else
			(void) originalWidth;
			(void) originalHeight;
#endif
		// Confirm button
		if (ImGui::Button("Confirm", ImVec2(200, 0)))
		{
			// Close popup
			m_isOpened = false;
			ImGui::CloseCurrentPopup();
		}

		ImGui::End();
	}
}
