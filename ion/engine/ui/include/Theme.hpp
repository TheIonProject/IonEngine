#pragma once

#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>

namespace ion
{
	struct Fonts
	{
		static ImFont* m_boldFont;
		//static ImFont* m_italicFont;
		static ImFont* m_regularFont;
	};

	void Color(ImGuiStyle*& style);
	void Style(ImGuiIO*& io, ImGuiStyle*& style);
	void UIFont(ImGuiIO*& io);

	void UITheme(void);


}
