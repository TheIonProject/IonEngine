#include "VertexArray.h"

#include "IonOpenGL.hpp"

namespace ion
{
	VertexArray::VertexArray(void)
	{
		glCreateVertexArrays(1, &m_id);
	}

	VertexArray::VertexArray(const Model& model)
	{
		glCreateVertexArrays(1, &m_id);

		CreateVertexBuffer(model.m_vertices);
		CreateIndexBuffer(model.m_indices);
	}


	void VertexArray::CreateVertexBuffer(const Vertex* vertices, int64_t bufferSize)
	{
		m_vbo.SetData(bufferSize, vertices);

		SetAllAttributes();
		BindVBO();
	}

	void VertexArray::CreateVertexBuffer(const std::vector<Vertex>& vertices)
	{
		const int64_t	bufferSize = static_cast<int64_t>
									(
										vertices.size() * sizeof(Vertex)
									);

		m_vbo.SetData(bufferSize, vertices.data());

		SetAllAttributes();
		BindVBO();
	}


	void VertexArray::CreateIndexBuffer(const uint32_t* indices, int64_t bufferSize)
	{
		m_ebo.SetData(bufferSize, indices);
		m_vertexCount = static_cast<uint32_t>(bufferSize / sizeof(uint32_t));

		BindEBO();
	}

	void VertexArray::CreateIndexBuffer(const std::vector<uint32_t>& indices)
	{
		// Get total buffer size
		const int64_t  bufferSize = static_cast<int64_t>
									(
										indices.size() * sizeof(uint32_t)
									);

		m_ebo.SetData(bufferSize, indices.data());
		m_vertexCount = static_cast<uint32_t>(indices.size());

		BindEBO();

	}

	void VertexArray::Draw(void)
	{
		glBindVertexArray(m_id);

		glDrawElements(GL_TRIANGLES, m_vertexCount, GL_UNSIGNED_INT, 0);

	}

	void VertexArray::Delete(void)
	{
		glDeleteVertexArrays(1, &m_id);

		m_id = 0;
	}

	VertexArray::~VertexArray(void)
	{
		Delete();
	}


	void VertexArray::SetAllAttributes(void)
	{
		// Attributes' position within a vertex. Relevant when working
		// with shaders
		const uint32_t		positionAttributePos = 0,
							vertexNormalAttributePos = 1,
							textureCoordAttributePos = 2;

		// Offset from the first element within the buffer
		constexpr uint32_t  positionOffset = 0,
							vertexNormalOffset = 3 * sizeof(float),
							textureCoordOffset = 6 * sizeof(float);


		SetAttribute(positionAttributePos, 3, positionOffset);
		SetAttribute(vertexNormalAttributePos, 3, vertexNormalOffset);
		SetAttribute(textureCoordAttributePos, 2, textureCoordOffset);

	}

	void VertexArray::SetAttribute(uint32_t position, int32_t size, uint32_t offset)
	{
		// This is NOT the VBO's id. This variable refers to the VBO's
		// position in the VAO's binding point, which is always 0 as we only have
		// 1 VBO per VBO. Changing this variable WILL lead to a segfault
		const uint32_t  vboBindingIndex = 0;

		glEnableVertexArrayAttrib(m_id, position);
		glVertexArrayAttribFormat(m_id, position, size, GL_FLOAT, GL_FALSE, offset);
		glVertexArrayAttribBinding(m_id, position, vboBindingIndex);
	}

	void VertexArray::BindVBO(void)
	{
		// Again, vboIndex refers to the VAO binding point index, and the offset is the first
		// elements within the buffer. Stride is the space between each occurence of an element
		constexpr  uint32_t	 vboIndex = 0, vboOffset = 0, vboStride = 8 * sizeof(float);

		glVertexArrayVertexBuffer(m_id, vboIndex, m_vbo.GetID(), vboOffset, vboStride);
	}

	void VertexArray::BindEBO(void)
	{
		glVertexArrayElementBuffer(m_id, m_ebo.GetID());
	}



}