//#include <filesystem>

#include "Application.h"
#include "Timer.hpp"

#include "IonDebug.hpp"
#include "IonOpenGL.hpp"

#include "EntityManager.h"
#include "Shader.h"

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

using namespace ion;

static void resize(GLFWwindow*, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main(void)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	{
		ION_SETUP_LOGS();

		ion::Application application;
		//ion::Timer timer;

		glfwSetWindowSizeCallback(application.GetWindowPtr(), resize);

		Entity& ball = EntityManager::CreateEntity();
		ball.AddComponent<Transform>();

		Model m;

		if (!m.ImportWavefront("testModels/model.obj"))
			__debugbreak();


		VertexArray vao(m);

		Shader shader("shaders/basic.vert", "shaders/basic.frag");

		ION_GL_BREAK(shader.Use());

		glClearColor(0.2f, 0.2f, 0.2f, 1.f);

		while (!glfwWindowShouldClose(application.GetWindowPtr()))
		{
			ION_GL_BREAK(glClear(GL_COLOR_BUFFER_BIT));
			ION_GL_BREAK(vao.Draw());

			ION_GL_BREAK(glfwSwapBuffers(application.GetWindowPtr()));
			ION_GL_BREAK(glfwPollEvents());
			//timer.CalcDeltaTime();
			//application.UpdateApplication(timer.GetDeltaTime());
		}

		std::cout << glGetError() << std::endl;
	}


	return 0;
}
