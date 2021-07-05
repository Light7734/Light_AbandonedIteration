#include "ltpch.h"
#include "glBuffers.h"

#include <glad/glad.h>

namespace Light {

	//** CONSTANT_BUFFER **//
	glConstantBuffer::glConstantBuffer(ConstantBufferIndex index, unsigned int size)
		: m_Index((int)index)
	{
		glCreateBuffers(1, &m_BufferID);
		glNamedBufferData(m_BufferID, size, nullptr, GL_DYNAMIC_DRAW);

		Bind();
	}

	glConstantBuffer::~glConstantBuffer()
	{
		glDeleteBuffers(1, &m_BufferID);
	}

	void glConstantBuffer::Bind()
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, m_Index, m_BufferID);
	}

	void* glConstantBuffer::Map()
	{
		void* map = glMapNamedBuffer(m_BufferID, GL_WRITE_ONLY);
		return map;
	}

	void glConstantBuffer::UnMap()
	{
		glUnmapNamedBuffer(m_BufferID);
	}

	//** VERTEX_BUFFER **//
	glVertexBuffer::glVertexBuffer(float* vertices, unsigned int count)
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

	//** INDEX_BUFFER **//
	glIndexBuffer::glIndexBuffer(unsigned int* indices, unsigned int count)
	{
		// generate indices if not provided
		bool hasIndices = !!indices;
		if (!hasIndices)
		{
			// check
			if (count % 6 != 0)
			{
				LT_ENGINE_WARN("glIndexBuffer::dxIndexBuffer: 'indices' can only be null if count is multiple of 6");
				LT_ENGINE_WARN("glIndexBuffer::glIndexBuffer: adding {} to 'count' -> {}", (6 - (count % 6)), count + (6 - (count % 6)));
				count = count + (6 - (count % 6));
			}

			// create indices
			indices = new unsigned int[count];
			unsigned int offset = 0;
			for (unsigned int i = 0; i < count; i += 6)
			{
				indices[i + 0] = offset + 0;
				indices[i + 1] = offset + 1;
				indices[i + 2] = offset + 2;

				indices[i + 3] = offset + 2;
				indices[i + 4] = offset + 3;
				indices[i + 5] = offset + 0;

				offset += 4;
			}
		}

		// create buffer
		glCreateBuffers(1, &m_BufferID);
		glNamedBufferData(m_BufferID, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);

		// delete indices
		if (!hasIndices)
			delete[] indices;
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