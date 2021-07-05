#pragma once

#include "Base.h"
#include "Graphics/Buffers.h"

namespace Light {

	class glConstantBuffer : public ConstantBuffer
	{
	private:
		unsigned int m_BufferID, m_Index;

	public:
		glConstantBuffer(ConstantBufferIndex index, unsigned int size);
		~glConstantBuffer();

		void Bind() override;

		void* Map() override;
		void UnMap() override;
	};

	//** VERTEX_BUFFER **//
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
	
	//** INDEX_BUFFER **//
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