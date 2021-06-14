#include "ltpch.h"
#include "Buffers.h"
#include "OpenGL/glBuffers.h"

#ifdef LIGHT_PLATFORM_WINDOWS
	#include "DirectX/dxBuffers.h"
#endif

#include "GraphicsContext.h"

namespace Light {


	VertexBuffer* VertexBuffer::Create(float* vertices, unsigned int stride, unsigned int count, void* sharedContext)
	{
		switch (GraphicsContext::GetGraphicsAPI())
		{
		case GraphicsAPI::OpenGL:
			return new glVertexBuffer(vertices, count);
			
		case GraphicsAPI::DirectX:
			return new dxVertexBuffer(vertices, stride, count, sharedContext);

		default:
			LT_ENGINE_ASSERT(false, "VertexBuffer::Create: invalid/unsupported GraphicsAPI {}", GraphicsContext::GetGraphicsAPI());
			return nullptr;
		}
	}

	IndexBuffer* IndexBuffer::Create(unsigned int* indices, unsigned int count, void* sharedContext)
	{
		switch (GraphicsContext::GetGraphicsAPI())
		{
		case GraphicsAPI::OpenGL:
			return new glIndexBuffer(indices, count);

		case GraphicsAPI::DirectX: LT_WIN(
			return new dxIndexBuffer(indices, count, sharedContext);)

		default:
			LT_ENGINE_ASSERT(false, "IndexBuffer::Create: invalid/unsupported GraphicsAPI {}", GraphicsContext::GetGraphicsAPI());
			return nullptr;
		}
	}

}