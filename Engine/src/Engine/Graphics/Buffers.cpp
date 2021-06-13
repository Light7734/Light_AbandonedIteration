#include "ltpch.h"
#include "Buffers.h"
#include "OpenGL/glBuffers.h"

#ifdef LIGHT_PLATFORM_WINDOWS
	#include "DirectX/dxBuffers.h"
#endif

#include "GraphicsContext.h"

namespace Light {


	VertexBuffer* VertexBuffer::Create(unsigned int stride, unsigned int count, float* vertices, void* sharedContext)
	{
		switch (GraphicsContext::GetGraphicsAPI())
		{
		case GraphicsAPI::OpenGL:
			return new glVertexBuffer(count, vertices);
			
		case GraphicsAPI::DirectX:
			return new dxVertexBuffer(count, stride, vertices, sharedContext);

		default:
			LT_ENGINE_ASSERT(false, "VertexBuffer::Create: invalid/unsupported GraphicsAPI {}", GraphicsContext::GetGraphicsAPI());
			return nullptr;
		}
	}

	IndexBuffer* IndexBuffer::Create(unsigned int count, unsigned int* indices, void* sharedContext)
	{
		switch (GraphicsContext::GetGraphicsAPI())
		{
		case GraphicsAPI::OpenGL:
			return new glIndexBuffer(count, indices);
		case GraphicsAPI::DirectX: LT_WIN(
			return new dxIndexBuffer(count, indices, sharedContext);
		)
		default:
			LT_ENGINE_ASSERT(false, "IndexBuffer::Create: invalid/unsupported GraphicsAPI {}", GraphicsContext::GetGraphicsAPI());
			return nullptr;
		}
	}

}