#pragma once

#include "Base.h"

namespace Light {

	class SharedContext;

	//* VERTEX BUFFER *//
	class VertexBuffer
	{
	public:
		static VertexBuffer* Create(float* vertices, unsigned int stride, unsigned int count, std::shared_ptr<SharedContext> sharedContext);

		virtual void* Map() = 0;
		virtual void UnMap() = 0;

		virtual void Bind() = 0;
		virtual void UnBind() = 0;

	protected:
		VertexBuffer() = default;
	};

	//* INDEX BUFFER *//
	class IndexBuffer
	{
	public:
		static IndexBuffer* Create(unsigned int* indices, unsigned int count, std::shared_ptr<SharedContext> sharedContext);

		virtual void Bind() = 0;
		virtual void UnBind() = 0;

	protected:
		IndexBuffer() = default;
	};

}