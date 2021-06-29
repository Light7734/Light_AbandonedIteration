#include "ltpch.h"
#include "Texture.h"

#include "GraphicsContext.h"

#include "OpenGL/glTexture.h"
#ifdef LIGHT_PLATFORM_WINDOWS
	// #todo:
#endif

namespace Light {

	Texture* Texture::Create(unsigned int width, unsigned int height, unsigned int components, unsigned char* pixels, std::shared_ptr<SharedContext> sharedContext)
	{
		switch (GraphicsContext::GetGraphicsAPI())
		{
		case GraphicsAPI::OpenGL:
			return new glTexture(width, height, components, pixels);

		case GraphicsAPI::DirectX: LT_WIN()

		default:
			LT_ENGINE_ASSERT(false, "Texture::Create: invalid/unsupported GraphicsAPI {}", GraphicsContext::GetGraphicsAPI());
			return nullptr;
		}
	}

}