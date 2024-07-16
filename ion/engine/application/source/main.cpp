//#include <filesystem>

#include "Application.h"

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

#include "Testing.h"
#include "Model.h"
#include "VertexArray.h"

#include "IonOpenGL.hpp"
#include "Shader.h"

#include "EntityManager.h"
#include "Transform.h"

static void resize(GLFWwindow* windowPtr, int width, int height)
{
	(void)windowPtr;

	ION_GL_BREAK(glViewport(0, 0, width, height));

}

using namespace ion;

int main(void)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	{
		ION_SETUP_LOGS();

		ion::Application application;
		//ion::Timer timer;

		int width, height;
		glfwGetWindowSize(application.GetWindowPtr(), &width, &height);

		ION_GL_BREAK(glViewport(0, 0, width, height));

		glfwSetWindowSizeCallback(application.GetWindowPtr(), resize);

		Entity& ball = EntityManager::CreateEntity();

		ball.AddComponent<Transform>();

		Transform& ballTransform = ball.GetComponent<Transform>();

		math::Matrix4f matrix = ballTransform.LocalMatrix();

		Entity& child = ball.CreateChild();
		child.AddComponent<Transform>();

		ion::Model model;

		model.ImportWavefront("testModels/model.obj");

		ion::VertexArray vao(model);

		ion::Shader shader("shaders/basic.vert", "shaders/basic.frag");

		shader.Use();

		while (!glfwWindowShouldClose(application.GetWindowPtr()))
		{
			// Clear background & color buffer
			ION_GL_BREAK(glClearColor(0.2f, 0.2f, 0.2f, 1.0f));
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