#include "ltpch.h"
#include "VertexLayout.h"
#include "OpenGL/glVertexLayout.h"

#ifdef LIGHT_PLATFORM_WINDOWS
	#include "DirectX/dxVertexLayout.h"
	#include "DirectX/dxSharedContext.h"
#endif

#include "GraphicsContext.h"

namespace Light {

	Ref<VertexLayout> VertexLayout::Create(Ref<VertexBuffer> vertexBuffer, Ref<Shader> shader, const std::vector<std::pair<std::string, VertexElementType>>& elements, Ref<SharedContext> sharedContext)
	{
		switch (GraphicsContext::GetGraphicsAPI())
		{
		case GraphicsAPI::OpenGL:
			return CreateRef<glVertexLayout>(vertexBuffer, elements);

		case GraphicsAPI::DirectX: LT_WIN(
			return CreateRef<dxVertexLayout>(shader, elements, std::static_pointer_cast<dxSharedContext>(sharedContext));)

		default:
			LT_ENGINE_ASSERT(false, "VertexLayout::Create: invalid/unsupported 'GraphicsAPI' {}", GraphicsContext::GetGraphicsAPI());
			return nullptr;
		}
	}

}