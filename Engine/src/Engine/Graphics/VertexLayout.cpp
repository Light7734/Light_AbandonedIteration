#include "ltpch.h"
#include "VertexLayout.h"
#include "OpenGL/glVertexLayout.h"

#ifdef LIGHT_PLATFORM_WINDOWS
	#include "DirectX/dxVertexLayout.h"
#endif

#include "GraphicsContext.h"

namespace Light {

	VertexLayout* VertexLayout::Create(VertexBuffer* buffer, Shader* shader, const std::vector<std::pair<std::string, VertexElementType>>& elements, void* sharedContext)
	{
		switch (GraphicsContext::GetGraphicsAPI())
		{
		case GraphicsAPI::OpenGL:
			return new glVertexLayout(buffer, elements);

		case GraphicsAPI::DirectX:
			return new dxVertexLayout(shader, elements, sharedContext);

		default:
			LT_ENGINE_ASSERT(false, "VertexLayout::Create: invalid/unsupported GraphicsAPI {}", GraphicsContext::GetGraphicsAPI());
			return nullptr;
		}
	}

}