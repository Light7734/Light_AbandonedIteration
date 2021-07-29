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

	//================================================== CONSTANT_BUFFER ==================================================//
	Scope<ConstantBuffer> ConstantBuffer::Create(ConstantBufferIndex index, unsigned int size, Ref<SharedContext> sharedContext)
	{
		switch (GraphicsContext::GetGraphicsAPI())
		{
		case GraphicsAPI::OpenGL:
			return CreateScope<glConstantBuffer>(index, size);

		case  GraphicsAPI::DirectX: LT_WIN(
			return CreateScope<dxConstantBuffer>(index, size, std::static_pointer_cast<dxSharedContext>(sharedContext));)

		default:
			LT_ENGINE_ASSERT(false, "ConstantBuffer::Create: invalid/unsupported 'GraphicsAPI' {}", GraphicsContext::GetGraphicsAPI());
			return nullptr;
		}
	}
	//================================================== CONSTANT_BUFFER ==================================================//

	//================================================== VERTEX_BUFFER ==================================================//
	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, unsigned int stride, unsigned int count, Ref<SharedContext> sharedContext)
	{
		switch (GraphicsContext::GetGraphicsAPI())
		{
		case GraphicsAPI::OpenGL:
			return CreateRef<glVertexBuffer>(vertices, count);
			
		case GraphicsAPI::DirectX: LT_WIN(
			return CreateRef<dxVertexBuffer>(vertices, stride, count, std::static_pointer_cast<dxSharedContext>(sharedContext));)

		default:
			LT_ENGINE_ASSERT(false, "VertexBuffer::Create: invalid/unsupported 'GraphicsAPI' {}", GraphicsContext::GetGraphicsAPI());
			return nullptr;
		}
	}
	//================================================== VERTEX_BUFFER ==================================================//

	//======================================== INDEX_BUFFER ========================================//
	Ref<IndexBuffer> IndexBuffer::Create(unsigned int* indices, unsigned int count, Ref<SharedContext> sharedContext)
	{
		switch (GraphicsContext::GetGraphicsAPI())
		{
		case GraphicsAPI::OpenGL:
			return CreateRef<glIndexBuffer>(indices, count);

		case GraphicsAPI::DirectX: LT_WIN(
			return CreateRef<dxIndexBuffer>(indices, count, std::dynamic_pointer_cast<dxSharedContext>(sharedContext));)

		default:
			LT_ENGINE_ASSERT(false, "IndexBuffer::Create: invalid/unsupported 'GraphicsAPI' {}", GraphicsContext::GetGraphicsAPI());
			return nullptr;
		}
	}
	//======================================== INDEX_BUFFER ========================================//

}