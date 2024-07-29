#include "Application.h"
#include "Timer.hpp"

#include "IonDebug.hpp"
#include "IonOpenGL.hpp"

#include "EntityManager.h"
#include "Shader.h"

#include "VertexArray.h"

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
		//glViewport(0, 0, 800, 600);
		ion::Timer timer;

		glfwSetWindowSizeCallback(application.GetWindowPtr(), resize);


		Entity& ball = EntityManager::CreateEntity();

		SmartRef<Entity> ball_s = ball;

		Transform& ballT = ball_s->AddComponent<Transform>();

		SmartRef<Transform> ballT_s = ball_s->GetSmartComponent<Transform>();

		ballT.Position().X() = 0.2f;

		ballT.UpdateGlobalMatrix();

		math::Matrix4f transform = ballT.GlobalMatrix();

		Entity& child = ball.CreateChild();

		child.AddComponent<Transform>();

		SmartRef<Transform> childT = child.GetSmartComponent<Transform>();

		SmartRef<Entity> grandChild_s = child.CreateChild();
		grandChild_s->AddComponent<Transform>();

		SmartRef<Transform> grandChildT_s = grandChild_s->GetSmartComponent<Transform>();


		childT->UpdateGlobalMatrix();

		math::Matrix4f transformChild = childT->GlobalMatrix();

		ION_CHECK(transform == transformChild);

		//child = EntityManager::GetEntity(0);

		Model m;

		if (!m.ImportWavefront("testModels/cube.obj"))
			__debugbreak();


		VertexArray vao(m);

		Shader shader("shaders/basic.vert", "shaders/basic.frag");


		childT->Scale() /= 3.f;

		glClearColor(0.2f, 0.2f, 0.2f, 1.f);

		ION_GL_BREAK(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
		while (!glfwWindowShouldClose(application.GetWindowPtr()))
		{
			timer.CalcDeltaTime();

			if (glfwGetKey(application.GetWindowPtr(), GLFW_KEY_UP))
				childT->Position().Y() += timer.GetDeltaTime();

			if (glfwGetKey(application.GetWindowPtr(), GLFW_KEY_DOWN))
				childT->Position().Y() -= timer.GetDeltaTime();

			if (glfwGetKey(application.GetWindowPtr(), GLFW_KEY_RIGHT))
			{
				childT->Position().X() += timer.GetDeltaTime();
				std::cout << childT->Position() << '\n';
			}

			if (glfwGetKey(application.GetWindowPtr(), GLFW_KEY_LEFT))
				childT->Position().X() -= timer.GetDeltaTime();

			if (glfwGetKey(application.GetWindowPtr(), GLFW_KEY_SPACE))
			{
				childT->Rotation().Z() += timer.GetDeltaTime();
				//std::cout << childT->Position() << '\n';
			}

			childT->UpdateGlobalMatrix();

			ION_GL_BREAK(glClear(GL_COLOR_BUFFER_BIT));

			ION_GL_BREAK(shader.Use());
			ION_GL_BREAK(shader.SetUniform("transform", childT->GlobalMatrix()));

			//ION_GL_BREAK(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));

			ION_GL_BREAK(vao.Draw());

			//glUseProgram(0);
			//ION_GL_BREAK(vao.Draw());

			ION_GL_BREAK(glfwSwapBuffers(application.GetWindowPtr()));
			ION_GL_BREAK(glfwPollEvents());
			//application.UpdateApplication(timer.GetDeltaTime());
		}

		std::cout << glGetError() << std::endl;
	}


	return 0;
}