#include "ltpch.h"
#include "glVertexBuffer.h"

#include <glad/glad.h>

namespace Light {

	glVertexBuffer::glVertexBuffer(unsigned int count, float* vertices)
	{
		glCreateBuffers(1, &m_BufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), vertices, GL_STATIC_DRAW);
	}

	glVertexBuffer::~glVertexBuffer()
	{
		glDeleteBuffers(1, &m_BufferID);
	}

	void glVertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	}

	void glVertexBuffer::UnBind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, NULL);
	}

}