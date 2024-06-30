#include <iostream>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>

#include "TitleBar.h"

void ion::MainMenuBar(void)
{

	if (ImGui::BeginMainMenuBar())
	{
		FileMenu();
		EditMenu();
		ViewMenu();

	}
	ImGui::EndMainMenuBar();
}

void ion::FileMenu(void)
{
	if (ImGui::BeginMenu("File"))
	{
		if (ImGui::MenuItem("Create"))
		{
			std::printf("Create\n");
		}
		else if (ImGui::MenuItem("Open", "Ctrl+O"))
		{
			std::printf("Open\n");
		}
		else if (ImGui::MenuItem("Save", "Ctrl+S"))
		{
			std::printf("Save\n");
		}
		else if (ImGui::MenuItem("Save As"))
		{
			std::printf("Save as\n");
		}
		else if (ImGui::MenuItem("Exit"))
			std::exit(0);
		ImGui::EndMenu();
	}
}

void ion::EditMenu(void)
{
	const char* addMenuItems[] =
	{
		"File",
		"GameObject",
		"Scene"
	};

	if (ImGui::BeginMenu("Edit"))
	{
		if (ImGui::BeginMenu("Add"))
		{
			for (const char* menuItem : addMenuItems)
			{
				ImGui::MenuItem(menuItem);
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenu();
	}
}

void ion::ViewMenu(void)
{
	// View menu to open a given window

	// TODO: consider changing this array for a better way to get windows
	const char* windows[] =
	{
		"Assets",
		"Console",
		"Editor View",
		"Game View",
		"Hierarchy"
	};

	if (ImGui::BeginMenu("View"))
	{
		for (const char* window : windows)
		{
			if (ImGui::MenuItem(window))
			{
				std::printf("%s\n", window);
			}
		}

		ImGui::EndMenu();
	}
}
