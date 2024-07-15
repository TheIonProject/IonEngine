/*

 _____                               _
|_   _|                             (_)
  | |  ___  _ __     ___ _ __   __ _ _ _ __   ___
  | | / _ \| '_ \   / _ \ '_ \ / _` | | '_ \ / _ \
 _| || (_) | | | | |  __/ | | | (_| | | | | |  __/
 \___/\___/|_| |_|  \___|_| |_|\__, |_|_| |_|\___|
								__/ |
							   |___/


NAME: Camera.cpp

DESCTIPTION: Camera for scene & game view. Handles perspective & view matrix (camera transformation).

AUTHOR: @MLev29 on GitHub


*/

#include <GLFW/glfw3.h>

#include <imgui/imgui.h>

#include "Camera.h"

ion::Camera::Camera(LibMath::Vector3f position, float speed)
{
	m_position = position;
	m_up = math::Vector3f::Up();
	m_forward = -math::Vector3f::Front();
	
	m_right = (m_forward.Cross(m_up)).Normalized();

	m_speed = speed;
	m_yaw = 0.0f;
	m_pitch = 0.0f;
}

LibMath::Matrix4f ion::Camera::GetPerspectiveMatrix(float near, float far, float fovDeg, float aspect) const noexcept
{
	float fovRad = fovDeg * DEG2RAD;
	
	const float tanAngle = tanf(fovRad * 0.5f);
	const float farMinusNear = far - near;

	const float perspectiveValues[4][4] =
	{
		{1.0f / (aspect * tanAngle), 0.0f, 0.0f, 0.0f},
		{0.0f, 1.0f / tanAngle, 0.0f, 0.0f},
		{0.0f, 0.0f, -(far + near) / (farMinusNear), -1.0f},
		{0.0f, 0.0f, -((2.0f * far * near) / (farMinusNear)), 0.0f}
	};

	return math::Matrix4f(perspectiveValues);
}

LibMath::Matrix4f ion::Camera::GetViewMatrix(void)
{
	// Camera forward direction
	math::Vector3f center = m_position + m_forward;
	math::Vector3f forward = (center - m_position).Normalized();
	m_right = (forward.Cross(m_up)).Normalized();
	math::Vector3f up = m_right.Cross(forward);

	const float viewValues[4][4] =
	{
		{m_right[0], up[0], -forward[0], 0.0f},
		{m_right[1], up[1], -forward[1], 0.0f},
		{m_right[2], up[2], -forward[2], 0.0f},
		{-(m_right.Dot(m_position)), -(up.Dot(m_position)), forward.Dot(m_position), 1.0f}
	};

	return math::Matrix4f(viewValues);
}

void ion::Camera::CameraUI(void)
{
	ImGui::Begin("Camera");
	
	ImGui::SliderFloat("X view", &m_position[0], -10.0f, 10.0f);
	ImGui::SliderFloat("Y view", &m_position[1], -10.0f, 10.0f);
	ImGui::SliderFloat("Z view", &m_position[2], -10.0f, 10.0f);

	ImGui::End();
}

void ion::Camera::CameraInput(GLFWwindow* windowPtr, float deltaTime)
{
	if (glfwGetKey(windowPtr, GLFW_KEY_W) == GLFW_PRESS)
		m_position += m_forward * m_speed * deltaTime;
	else if (glfwGetKey(windowPtr, GLFW_KEY_S) == GLFW_PRESS)
		m_position += -m_forward * m_speed * deltaTime;
	
	if (glfwGetKey(windowPtr, GLFW_KEY_A) == GLFW_PRESS)
		m_position += -m_right * m_speed * deltaTime;
	else if (glfwGetKey(windowPtr, GLFW_KEY_D) == GLFW_PRESS)
		m_position += m_right * m_speed * deltaTime;

	if (glfwGetKey(windowPtr, GLFW_KEY_Q) == GLFW_PRESS)
		m_position -= math::Vector3f::Up() * m_speed * deltaTime;
	else if (glfwGetKey(windowPtr, GLFW_KEY_E) == GLFW_PRESS)
		m_position += math::Vector3f::Up() * m_speed * deltaTime;
}
