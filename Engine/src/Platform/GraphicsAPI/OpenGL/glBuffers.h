#pragma once

#include "Base.h"
#include "Graphics/Buffers.h"

namespace Light {

	class glVertexBuffer : public VertexBuffer
	{
	private:
		unsigned int m_BufferID;

	public:
		glVertexBuffer(float* vertices, unsigned int count);
		~glVertexBuffer();

		void* Map() override;
		void UnMap() override;

		void Bind() override;
		void UnBind() override;
	};
	
	class glIndexBuffer : public IndexBuffer
	{
	private:
		unsigned int m_BufferID;

	public:
		glIndexBuffer(unsigned int* indices, unsigned int count);
		~glIndexBuffer();

		void Bind() override;
		void UnBind() override;
	};

}