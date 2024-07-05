#pragma once

#include "FrameBuffer.h"
//#include "Testing.h"

namespace ion
{
	enum ViewportMode
	{
		FILL_WINDOW,
		HD_RATIO,
		CUSTOM_RATIO // TODO: finish custom aspect ratio for viewport
	};

	class Viewport
	{
	public:
		Viewport(void);
		Viewport(ViewportMode const viewportMode);
		~Viewport(void) = default;

		ViewportMode GetViewportMode(void) const noexcept;
		void SetViewportMode(ViewportMode const viewportMode);

		void UpdateViewport(FrameBuffer& frameBuffer);
	private:
		void SetViewportSize(void);
		void ViewportPosition(void);
		void OptionBarUI(void);

		ImVec2 m_position;
		ViewportMode m_currentMode;
		float m_width;
		float m_height;

	};
}