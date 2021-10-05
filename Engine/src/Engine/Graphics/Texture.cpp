#include "ltpch.h"
#include "Texture.h"
#include "OpenGL/glTexture.h"

#ifdef LIGHT_PLATFORM_WINDOWS
	#include "DirectX/dxTexture.h"
	#include "DirectX/dxSharedContext.h"
#endif

#include "GraphicsContext.h"

namespace Light {

	Ref<Texture>Texture::Create(unsigned int width, unsigned int height, unsigned int components, unsigned char* pixels, Ref<SharedContext> sharedContext, const std::string& filePath)
	{
		switch (GraphicsContext::GetGraphicsAPI())
		{
		case GraphicsAPI::OpenGL:
			return CreateRef<glTexture>(width, height, components, pixels, filePath);

		case GraphicsAPI::DirectX: LT_WIN(
			return CreateRef<dxTexture>(width, height, components, pixels, std::static_pointer_cast<dxSharedContext>(sharedContext), filePath);)

		default:
			LT_ENGINE_ASSERT(false, "Texture::Create: invalid/unsupported 'GraphicsAPI' {}", GraphicsContext::GetGraphicsAPI());
			return nullptr;
		}
	}

	Texture::Texture(const std::string& filePath):
		m_FilePath(filePath)
	{
	}

}