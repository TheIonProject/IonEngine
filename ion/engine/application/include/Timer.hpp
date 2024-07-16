#pragma once

#include <GLFW/glfw3.h>

namespace ion
{
	class Timer
	{
	public:
		Timer(void) = default;
		~Timer(void) = default;

		inline void CalcDeltaTime(void)
		{
			float currentTime = static_cast<float>(glfwGetTime());

			m_deltaTime = currentTime - m_prevTime;

			m_prevTime = currentTime;
		}

		inline float GetDeltaTime(void) const noexcept
		{
			return m_deltaTime;
		}
	private:
		float m_deltaTime;

		float m_prevTime;
	};
}