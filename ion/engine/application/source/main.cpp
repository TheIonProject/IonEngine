//#include <filesystem>

#include "Application.h"
#include "Timer.hpp"

#include "IonDebug.hpp"

// For memory leaks
// Must be after #includes for ImGui compatibility
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
		ION_SETUP_LOGS();

		ion::Application application;
		ion::Timer timer;

		while (!glfwWindowShouldClose(application.GetWindowPtr()))
		{
			timer.CalcDeltaTime();
			application.UpdateApplication(timer.GetDeltaTime());
		}

		std::cout << glGetError() << std::endl;
	}


	return 0;
}
