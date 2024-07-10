#include <string>

#include "Theme.hpp"

#define FONT_FILE_PATH "../../../assets/fonts/"

ImFont* ion::Fonts::m_boldFont = nullptr;
//ImFont* ion::Fonts::m_italicFont = nullptr;
ImFont* ion::Fonts::m_regularFont = nullptr;

void ion::Color(void)
{
	ImVec4* colors = ImGui::GetStyle().Colors;
	(void) colors;

}

void ion::Style(ImGuiIO*& io)
{
	ImGuiStyle& style = ImGui::GetStyle();
	style.TabRounding = 2.5f;

	if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}
}

void ion::UIFont(ImGuiIO*& io)
{
	constexpr int fontSize = 18;

	// TODO: add font file path
	Fonts::m_boldFont = io->Fonts->AddFontFromFileTTF((std::string(FONT_FILE_PATH) + std::string("Manrope-Bold.ttf")).c_str(), fontSize);
	//Fonts::m_italicFont = io->Fonts->AddFontFromFileTTF((std::string(FONT_FILE_PATH) + std::string("Manrope-Light.ttf")).c_str(), fontSize);
	Fonts::m_regularFont = io->Fonts->AddFontFromFileTTF((std::string(FONT_FILE_PATH) + std::string("Manrope-Light.ttf")).c_str(), fontSize);
	io->Fonts->Build();
}

void ion::UITheme(void)
{
	ImGuiIO* io = &ImGui::GetIO();

	Color();
	Style(io);
	UIFont(io);
}