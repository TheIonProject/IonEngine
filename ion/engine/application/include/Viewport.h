/*

 _____                               _
|_   _|                             (_)
  | |  ___  _ __     ___ _ __   __ _ _ _ __   ___
  | | / _ \| '_ \   / _ \ '_ \ / _` | | '_ \ / _ \
 _| || (_) | | | | |  __/ | | | (_| | | | | |  __/
 \___/\___/|_| |_|  \___|_| |_|\__, |_|_| |_|\___|
								__/ |
							   |___/


NAME: Viewport.h

DESCTIPTION: Viewport class, made to handle scene view window

AUTHOR: @MLev29 on GitHub


*/

#pragma once

#include <imgui/imgui.h>

#include "math/Matrix4.hpp"

#include "FrameBuffer.h"
#include "VertexArray.h"
#include "Camera.h"

namespace ion
{
	enum ViewportMode
	{
		FILL_WINDOW,
		HD_RATIO,
		CUSTOM_RATIO
	};

	class Viewport
	{
	public:
		Viewport(void) = default;
		Viewport(ViewportMode const viewportMode);
		Viewport(Viewport const& viewport);
		~Viewport(void);

		ViewportMode GetViewportMode(void) const noexcept;
		bool GetWindowActive(void) const noexcept;
		void SetViewportMode(ViewportMode const viewportMode);

		void InitViewport(void);
		void UpdateViewport(GLFWwindow* windowPtr, FrameBuffer& frameBuffer);

		
		FrameBuffer* m_frameBuffer;
		Camera* m_camera;
	private:
		void SetViewportSize(void);
		void ViewportPosition(void);
		void OptionBarUI(void);
		void CustomAspectModal(int const originalWidth, int const originalHeight);

		VertexArray* m_vertexArray = nullptr;
		ImVec2 m_position;
		ViewportMode m_currentMode;
		ViewportMode m_prevMode;
		int m_width;
		int m_height;
		bool m_isOpened;
		bool m_isWindowActive;
	};
}