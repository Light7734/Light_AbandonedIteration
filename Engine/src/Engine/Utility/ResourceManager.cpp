#include "ltpch.h"
#include "ResourceManager.h"

#include "Graphics/GraphicsContext.h"
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"

#include <stb_image.h>

namespace Light {

	ResourceManager* ResourceManager::s_Context = nullptr;

	ResourceManager* ResourceManager::Create(std::shared_ptr<SharedContext> sharedContext)
	{
		return new ResourceManager(sharedContext);
	}

	ResourceManager::ResourceManager(std::shared_ptr<SharedContext> sharedContext)
		: m_SharedContext(sharedContext)
	{
		LT_ENGINE_ASSERT(!s_Context, "ResourceManager::ResourceManager: an instance of 'ResourceManager' already exists, do not construct this class!");
		s_Context = this;

		stbi_set_flip_vertically_on_load(true);
	}
	
	void ResourceManager::CreateShaderImpl(const std::string& name, const std::string& vertexSource, const std::string& pixelSource)
	{
		// delim
		std::string delim = GraphicsContext::GetGraphicsAPI() == GraphicsAPI::OpenGL ? "GLSL" :
		                    GraphicsContext::GetGraphicsAPI() == GraphicsAPI::DirectX ? "HLSL" : NULL;

		// check
		LT_ENGINE_ASSERT(!vertexSource.empty(), "ResourceManager::CreateShader: 'vertexSource' is empty");
		LT_ENGINE_ASSERT(!vertexSource.empty(), "ResourceManager::CreateShader: 'pixelSource' is empty");
		LT_ENGINE_ASSERT(!delim.empty(), "ResourceManager::LoadShader: invalid/unsupported 'GraphicsAPI': {}", GraphicsContext::GetGraphicsAPI());

		// save to string
		std::string vsSource = vertexSource;
		std::string psSource = pixelSource;

		// extract shader source
		ResourceManager::ExtractShaderSource(vsSource, delim);
		ResourceManager::ExtractShaderSource(psSource, delim);

		// create shader
		m_Shaders[name] = std::shared_ptr<Shader>(Shader::Create(vsSource, psSource, m_SharedContext));
	}

	void ResourceManager::LoadShaderImpl(const std::string& name, const std::string& vertexPath, const std::string& pixelPath)
	{
		// check
		LT_ENGINE_ASSERT(!vertexPath.empty(), "ResourceManager::LoadShader: 'vertexPath' is empty");
		LT_ENGINE_ASSERT(!pixelPath.empty(), "ResourceManager::LoadShader: 'pixelPath' is empty");

		std::string vPath = vertexPath + (GraphicsContext::GetGraphicsAPI() == GraphicsAPI::OpenGL ? ".glsl" : ".hlsl");
		std::string pPath = pixelPath  + (GraphicsContext::GetGraphicsAPI() == GraphicsAPI::OpenGL ? ".glsl" : ".hlsl");

		// initialize
		std::ifstream vsStream(vPath), psStream(pPath);
		std::stringstream vsSS, psSS; // pss pss pss pss :D 
		std::string line;

		// read
		while (std::getline(vsStream, line))
			vsSS << line << '\n';

		while (std::getline(psStream, line))
			psSS << line << '\n';

		// create shader
		m_Shaders[name] = std::shared_ptr<Shader>(Shader::Create(vsSS.str(), psSS.str(), m_SharedContext));
	}

	void ResourceManager::LoadTextureImpl(const std::string& name, const std::string& path, unsigned int desiredComponents /* = 4u */)
	{
		// load image
		int width, height, components;
		unsigned char* pixels = stbi_load(path.c_str(), &width, &height, &components, desiredComponents);
		
		// check
		LT_ENGINE_ASSERT(pixels, "ResourceManager::LoadTexture: failed to load texture <{}>, 'path': {}", name, path);
		if (components != desiredComponents)
		{
			LT_ENGINE_WARN("ResourceManager::LoadTexture: image file compoenents != 'desiredComponents' ({} - {})", components, desiredComponents);
			LT_ENGINE_WARN("ResourceManager::LoadTexture: <{}> 'path': {}", name, path);
		}

		// create texture
		m_Textures[name] = std::shared_ptr<Texture>(Texture::Create(width, height, components, pixels, m_SharedContext));
	}

	void ResourceManager::ExtractShaderSource(std::string& src, const std::string& delim)
	{
		size_t begDelimPos, endDelimPos;

		// find begin and end delimiter (eg. +GLSL ... -GLSL )
		begDelimPos = src.find('+' + delim) + 5;
		endDelimPos = src.find('-' + delim);

		// check
		LT_ENGINE_ASSERT(begDelimPos != std::string::npos + 5,
		                 "Shader::ExtractShaderSource: failed to find the start delimeter in shader source, delim: {}, shader:\n{}",
		                 delim, src);


		LT_ENGINE_ASSERT(endDelimPos != std::string::npos,
		                 "Shader::ExtractShaderSource: failed to find the end delimeter in shader source, delim: {}, shader:\n{}",
		                 delim, src);

		// extract the shader
		src = src.substr(begDelimPos, endDelimPos - begDelimPos);
	}

}