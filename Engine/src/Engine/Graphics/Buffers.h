#pragma once

#include "Base.h"

namespace Light {

	class VertexBuffer
	{
	public:
		static VertexBuffer* Create(unsigned int count, float* vertices);

		virtual void Bind() = 0;
		virtual void UnBind() = 0;

	protected:
		VertexBuffer() = default;
	};

	class IndexBuffer
	{
	public:
		static IndexBuffer* Create(unsigned int count, unsigned int* indices);

		virtual void Bind() = 0;
		virtual void UnBind() = 0;

	protected:
		IndexBuffer() = default;
	};

}