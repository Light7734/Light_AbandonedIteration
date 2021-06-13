#include "ltpch.h"
#include "glBuffers.h"

#include <glad/glad.h>

namespace Light {

	glVertexBuffer::glVertexBuffer(unsigned int count, float* vertices)
	{
		glCreateBuffers(1, &m_BufferID);
		glNamedBufferData(m_BufferID, count * sizeof(float), vertices, GL_DYNAMIC_DRAW);
	}

	glVertexBuffer::~glVertexBuffer()
	{
		glDeleteBuffers(1, &m_BufferID);
	}

	void* glVertexBuffer::Map()
	{
		return glMapNamedBuffer(m_BufferID, GL_WRITE_ONLY);
	}

	void glVertexBuffer::UnMap()
	{
		glUnmapNamedBuffer(m_BufferID);
	}

	void glVertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	}

	void glVertexBuffer::UnBind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, NULL);
	}

	glIndexBuffer::glIndexBuffer(unsigned int count, unsigned int* indices)
	{
		glCreateBuffers(1, &m_BufferID);
		glNamedBufferData(m_BufferID, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	}

	glIndexBuffer::~glIndexBuffer()
	{
		glDeleteBuffers(1, &m_BufferID);
	}

	void glIndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
	}

	void glIndexBuffer::UnBind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
	}

}