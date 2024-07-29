/*

 _____                               _
|_   _|                             (_)
  | |  ___  _ __     ___ _ __   __ _ _ _ __   ___
  | | / _ \| '_ \   / _ \ '_ \ / _` | | '_ \ / _ \
 _| || (_) | | | | |  __/ | | | (_| | | | | |  __/
 \___/\___/|_| |_|  \___|_| |_|\__, |_|_| |_|\___|
								__/ |
							   |___/


NAME: Camera.h

DESCTIPTION: Camera for scene & game view. Handles perspective & view matrix (camera transformation).

AUTHOR: @MLev29 on GitHub


*/

#pragma once

#include <math/Matrix4.hpp>
#include <math/Vector3.hpp>

#include <IonExport.h>

namespace ion
{
	class ION_API Camera
	{
	public:

		Camera(void) = default;
		Camera(LibMath::Vector3f position, float speed);
		~Camera(void) = default;

		LibMath::Matrix4f GetPerspectiveMatrix(float near, float far, float fovDeg, float aspect) const noexcept;
		LibMath::Matrix4f GetViewMatrix(void);
		void SetLastCursorPos(LibMath::Vector2f const& position);

		void CameraUI(void);
		void CameraInput(GLFWwindow* windowPtr, float deltaTime);
		void MouseMotion(LibMath::Vector2f const& cursorPos, float deltaTime);

	private:
		// View matrix
		LibMath::Vector3f m_position;
		LibMath::Vector3f m_up;
		LibMath::Vector3f m_right;
		LibMath::Vector3f m_forward;
		LibMath::Vector2f m_lastCursorPos;

		// Transformation
		float m_speed;
		float m_angularSpeed;
		float m_yaw;
		float m_pitch;


	};
}