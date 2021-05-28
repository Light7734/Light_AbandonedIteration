#include "ltpch.h"
#include "Buffers.h"
#include "OpenGL/glBuffers.h"

#include "GraphicsContext.h"

namespace Light {


	VertexBuffer* VertexBuffer::Create(unsigned int count, float* vertices)
	{
		switch (GraphicsContext::GetGraphicsAPI())
		{
		case GraphicsAPI::OpenGL:
			return new glVertexBuffer(count, vertices);
		default:
			LT_ENGINE_ASSERT(false, "VertexBuffer::Create: invalid/unsupported GraphicsAPI {}", GraphicsContext::GetGraphicsAPI());
			return nullptr;
		}
	}

	IndexBuffer* IndexBuffer::Create(unsigned int count, unsigned int* indices)
	{
		switch (GraphicsContext::GetGraphicsAPI())
		{
		case GraphicsAPI::OpenGL:
			return new glIndexBuffer(count, indices);
		default:
			LT_ENGINE_ASSERT(false, "IndexBuffer::Create: invalid/unsupported GraphicsAPI {}", GraphicsContext::GetGraphicsAPI());
			return nullptr;
		}
	}

}