#pragma once

#include "Base.h"

namespace Light {

	class VertexBuffer
	{
	public:
		static VertexBuffer* Create(unsigned int stride, unsigned int count, float* vertices, void* sharedContext);

		virtual void* Map() = 0;
		virtual void UnMap() = 0;

		virtual void Bind() = 0;
		virtual void UnBind() = 0;

	protected:
		VertexBuffer() = default;
	};

	class IndexBuffer
	{
	public:
		static IndexBuffer* Create(unsigned int count, unsigned int* indices, void* sharedContext);

		virtual void Bind() = 0;
		virtual void UnBind() = 0;

	protected:
		IndexBuffer() = default;
	};

}