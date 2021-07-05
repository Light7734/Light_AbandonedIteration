#pragma once

#include "Base.h"

namespace Light {

	class SharedContext;

	enum ConstantBufferIndex
	{
		ViewProjection = 0u
	};

	//* CONSTANT_BUFFER *//
	class ConstantBuffer
	{
	public:
		static ConstantBuffer* Create(ConstantBufferIndex index, unsigned int size, std::shared_ptr<SharedContext> sharedContext);

		virtual void Bind() = 0;

		virtual void* Map() = 0;
		virtual void UnMap() = 0;
	};

	//* VERTEX_BUFFER *//
	class VertexBuffer
	{
	public:
		static VertexBuffer* Create(float* vertices, unsigned int stride, unsigned int count, std::shared_ptr<SharedContext> sharedContext);

		virtual ~VertexBuffer() = default;

		virtual void* Map() = 0;
		virtual void UnMap() = 0;

		virtual void Bind() = 0;
		virtual void UnBind() = 0;

	protected:
		VertexBuffer() = default;
	};

	//* INDEX_BUFFER *//
	class IndexBuffer
	{
	public:
		static IndexBuffer* Create(unsigned int* indices, unsigned int count, std::shared_ptr<SharedContext> sharedContext);

		virtual ~IndexBuffer() = default;

		virtual void Bind() = 0;
		virtual void UnBind() = 0;

	protected:
		IndexBuffer() = default;
	};

}