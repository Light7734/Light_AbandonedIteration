#include "ltpch.h"
#include "Buffers.h"
#include "OpenGL/glBuffers.h"

#include "SharedContext.h"

#ifdef LIGHT_PLATFORM_WINDOWS
	#include "DirectX/dxBuffers.h"
	#include "DirectX/dxSharedContext.h"
#endif

#include "GraphicsContext.h"

namespace Light {

	//* VERTEX_BUFFER *//
	VertexBuffer* VertexBuffer::Create(float* vertices, unsigned int stride, unsigned int count, std::shared_ptr<SharedContext> sharedContext)
	{
		switch (GraphicsContext::GetGraphicsAPI())
		{
		case GraphicsAPI::OpenGL:
			return new glVertexBuffer(vertices, count);
			
		case GraphicsAPI::DirectX: LT_WIN(
			return new dxVertexBuffer(vertices, stride, count, std::static_pointer_cast<dxSharedContext>(sharedContext));)

		default:
			LT_ENGINE_ASSERT(false, "VertexBuffer::Create: invalid/unsupported 'GraphicsAPI' {}", GraphicsContext::GetGraphicsAPI());
			return nullptr;
		}
	}

	//* INDEX_BUFFER *//
	IndexBuffer* IndexBuffer::Create(unsigned int* indices, unsigned int count, std::shared_ptr<SharedContext> sharedContext)
	{
		switch (GraphicsContext::GetGraphicsAPI())
		{
		case GraphicsAPI::OpenGL:
			return new glIndexBuffer(indices, count);

		case GraphicsAPI::DirectX: LT_WIN(
			return new dxIndexBuffer(indices, count, std::dynamic_pointer_cast<dxSharedContext>(sharedContext));)

		default:
			LT_ENGINE_ASSERT(false, "IndexBuffer::Create: invalid/unsupported 'GraphicsAPI' {}", GraphicsContext::GetGraphicsAPI());
			return nullptr;
		}
	}

}