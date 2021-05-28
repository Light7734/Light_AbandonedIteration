#pragma once

#include "Base.h"
#include "Graphics/Buffers.h"

namespace Light {

	class glVertexBuffer : public VertexBuffer
	{
	private:
		unsigned int m_BufferID;

	public:
		glVertexBuffer(unsigned int count, float* vertices);
		~glVertexBuffer();

		void Bind() override;
		void UnBind() override;
	};
	
	class glIndexBuffer : public IndexBuffer
	{
	private:
		unsigned int m_BufferID;

	public:
		glIndexBuffer(unsigned int count, unsigned int* indices);
		~glIndexBuffer();

		void Bind() override;
		void UnBind() override;
	};

}