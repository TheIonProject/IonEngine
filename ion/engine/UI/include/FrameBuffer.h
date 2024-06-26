#pragma once

namespace ion
{
	class FrameBuffer
	{
	public:
		FrameBuffer(void) = default;

		~FrameBuffer(void);

		void InitFrameBuffer(void);

		unsigned int GetFrameTexture(void) const noexcept;
		unsigned int GetFrameBuffer(void) const noexcept;
		void RescaleFrameBuffer(GLsizei width, GLsizei height);

		void Bind(void) const;
		void UnBind(void) const;
	private:
		void BindTexture(GLsizei width, GLsizei height);

		GLuint m_fbo = 0;
		GLuint m_texture = 0;
		GLuint m_rbo = 0;
		const GLint m_width = 800;
		const GLint m_height = 600;
	};
}