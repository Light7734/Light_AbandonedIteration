#include "ltpch.h"
#include "VertexLayout.h"
#include "OpenGL/glVertexLayout.h"

#include "GraphicsContext.h"
#include "Buffers.h"

namespace Light {

	VertexLayout* VertexLayout::Create(VertexBuffer* buffer, const std::vector<VertexElementType> elements)
	{
		switch (GraphicsContext::GetGraphicsAPI())
		{
		case GraphicsAPI::OpenGL:
			return new glVertexLayout(buffer, elements);

		default:
			LT_ENGINE_ASSERT(false, "VertexLayout::Create: invalid/unsupported GraphicsAPI {}", GraphicsContext::GetGraphicsAPI());
			return nullptr;
		}
	}

}