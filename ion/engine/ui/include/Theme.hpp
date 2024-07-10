#pragma once

#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>

#define BACKGROUND_COLOR			0.121f,0.121f, 0.121f, 1.0f
#define BACKGROUND_WINDOW_COLOR		0.09f, 0.09f, 0.09f, 1.0f
#define PRIMARY_COLOR				0.14f, 0.14f, 0.14f, 1.0f
#define SECONDARY_COLOR				
#define ACCENT_COLOR				
#define TEXT_COLOR					0.568f, 0.568f, 0.568f, 1.0f


namespace ion
{
	struct Fonts
	{
		static ImFont* m_boldFont;
		//static ImFont* m_italicFont;
		static ImFont* m_regularFont;
	};

	void Color(void);
	void Style(ImGuiIO*& io);
	void UIFont(ImGuiIO*& io);

	void UITheme(void);


}
