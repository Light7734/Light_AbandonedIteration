#include "ltpch.h"
#include "ResourceManager.h"

#include "Graphics/GraphicsContext.h"
#include "Graphics/Shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>g

namespace Light {

	ResourceManager* ResourceManager::s_Context = nullptr;

	ResourceManager* ResourceManager::Create(std::shared_ptr<SharedContext> sharedContext)
	{
		return new ResourceManager(sharedContext);
	}

	ResourceManager::ResourceManager(std::shared_ptr<SharedContext> sharedContext)
		: m_SharedContext(sharedContext)
	{
		LT_ENGINE_ASSERT(!s_Context, "ResourceManager::ResourceManager: an instance of 'resource manager' already exists, do not construct this class");
		s_Context = this;
	}

	void ResourceManager::CreateShaderImpl(const std::string& name, const std::string& vertexSource, const std::string& pixelSource)
	{
		// delim
		std::string delim = GraphicsContext::GetGraphicsAPI() == GraphicsAPI::OpenGL ? "GLSL" :
		                    GraphicsContext::GetGraphicsAPI() == GraphicsAPI::DirectX ? "HLSL" : NULL;

		// check
		LT_ENGINE_ASSERT(!vertexSource.empty(), "ResourceManager::CreateShader: vertex source is empty");
		LT_ENGINE_ASSERT(!vertexSource.empty(), "ResourceManager::CreateShader: pixel source is empty");
		LT_ENGINE_ASSERT(!delim.empty(), "ResourceManager::LoadShader: invalid/unsupported graphics api: {}", GraphicsContext::GetGraphicsAPI());

		// save to string
		std::string vsSource = vertexSource;
		std::string psSource = pixelSource;

		// extract source
		ResourceManager::ExtractShaderSource(vsSource, delim);
		ResourceManager::ExtractShaderSource(psSource, delim);

		// create shader
		m_Shaders[name] = std::shared_ptr<Shader>(Shader::Create(vsSource, psSource, m_SharedContext));
	}

	void ResourceManager::LoadShaderImpl(const std::string& name, const std::string& vertexPath, const std::string& pixelPath)
	{
		// check
		LT_ENGINE_ASSERT(!vertexPath.empty(), "ResourceManager::LoadShader: vertex path is empty");
		LT_ENGINE_ASSERT(!pixelPath.empty(), "ResourceManager::LoadShader: pixel path is empty");

		// initialize
		std::ifstream vsStream(vertexPath), psStream(pixelPath);
		std::stringstream vsSS, psSS; // pss pss pss pss :D 
		std::string vertexSource, pixelSource;
		std::string line;

		// delim
		std::string delim = GraphicsContext::GetGraphicsAPI() == GraphicsAPI::OpenGL ? "GLSL" :
		                    GraphicsContext::GetGraphicsAPI() == GraphicsAPI::DirectX ? "HLSL" : NULL;

		// check
		LT_ENGINE_ASSERT(!delim.empty(), "ResourceManager::LoadShader: invalid/unsupported graphics api: {}", GraphicsContext::GetGraphicsAPI());
		LT_ENGINE_ASSERT(vsStream.is_open(), "ResourceManager::LoadShader: invalid vertex path: {}", vertexPath);
		LT_ENGINE_ASSERT(psStream.is_open(), "ResourceManager::LoadShader: invalid pixel path: {}", pixelPath);

		// read
		while (std::getline(vsStream, line))
			vsSS << line << '\n';

		while (std::getline(psStream, line))
			psSS << line << '\n';

		// save to string
		vertexSource = vsSS.str();
		pixelSource = psSS.str();

		// extract source
		ResourceManager::ExtractShaderSource(vertexSource, delim);
		ResourceManager::ExtractShaderSource(pixelSource, delim);

		// create shader
		m_Shaders[name] = std::shared_ptr<Shader>(Shader::Create(vertexSource, pixelSource, m_SharedContext));
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