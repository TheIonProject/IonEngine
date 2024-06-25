#include "core/Application.h"

// For memory leaks
// Must be after #includes for imgui compatibility
#define _CRTDBG_MAP_ALLOC
#include<iostream>
#include <crtdbg.h>
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

int main(void)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	{
		Ion::Application application;

		while (!glfwWindowShouldClose(application.GetWindowPtr()))
		{
			application.UpdateApplication();
		}
	}

	return 0;
}