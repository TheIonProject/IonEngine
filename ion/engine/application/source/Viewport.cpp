#include <iostream>
#include <exception>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>

#include "Viewport.h"
#include "Testing.h"


ion::Viewport::Viewport(void)
{
	m_currentMode = ViewportMode::FILL_WINDOW;
	m_width = 0.0f;
	m_height = 0.0f;
	m_position = ImVec2(0.0f, 0.0f);
}

ion::Viewport::Viewport(ViewportMode const viewportMode)
{
	m_currentMode = viewportMode;
	m_width = 0.0f;
	m_height = 0.0f;
	m_position = ImVec2(0.0f, 0.0f);
}

ion::ViewportMode ion::Viewport::GetViewportMode(void) const noexcept
{
	return m_currentMode;
}

void ion::Viewport::SetViewportMode(ViewportMode const viewportMode)
{
	m_currentMode = viewportMode;
}

void ion::Viewport::UpdateViewport(FrameBuffer& frameBuffer)
{
	//bool* e = nullptr;
	ImGui::Begin("Editor View", nullptr, ImGuiWindowFlags_MenuBar /*| ImGuiWindowFlags_NoCollapse*/);

	ImVec2 regionSize = ImGui::GetContentRegionAvail();
	const GLsizei regionWidth = static_cast<GLsizei>(regionSize.x);
	const GLsizei regionHeight = static_cast<GLsizei>(regionSize.y);

	frameBuffer.RescaleFrameBuffer(
		regionWidth,
		regionHeight
	);

	glViewport(0, 0, regionWidth, regionHeight);

	ImVec2 pos = ImGui::GetCursorScreenPos();

	OptionBarUI();
	SetViewportSize();
	ViewportPosition();

	ImGui::GetWindowDrawList()->AddImage(
		(void*) static_cast<uint64_t>(frameBuffer.GetFrameBuffer()),
		ImVec2(m_position.x, m_position.y),
		ImVec2(m_position.x + m_width, m_position.y + m_height),
		ImVec2(0, 1),
		ImVec2(1, 0)
	);



	ImGui::End();

	frameBuffer.Bind();

	glUseProgram(g_shader);
	glBindVertexArray(g_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
	glUseProgram(0);

	frameBuffer.UnBind();
}

void ion::Viewport::SetViewportSize(void)
{
	// Value obtained from dividing 1080 by 1920
	constexpr float hdAspectRatio = 0.5625f;
	ImVec2 windowSize = ImGui::GetContentRegionAvail();

	// TODO: add custom input for width & height
	const float windowWidth = 500.0f;
	const float windowHeight = 500.0f;

	switch (m_currentMode)
	{
	case ViewportMode::HD_RATIO:
		m_width = windowSize.x;
		m_height = m_width * hdAspectRatio;
		break;
	case ViewportMode::FILL_WINDOW:
		m_width = windowSize.x;
		m_height = windowSize.y;
		break;
	case ViewportMode::CUSTOM_RATIO:
		m_width = windowWidth;
		m_height = windowHeight;
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
	m_position.y = pos.y + (0.5f * (regionSize.y - m_height));
}

void ion::Viewport::OptionBarUI(void)
{
	const char* options[] =
	{
		"Free aspect",
		"16:9 HD",
		"Custom (WIP)"
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
					currentOption = options[i];
					m_currentMode = static_cast<ViewportMode>(i);
				}

				if (isSelected)
					ImGui::SetItemDefaultFocus();
			}

			ImGui::EndCombo();
		}

		ImGui::EndMenuBar();
	}
}
