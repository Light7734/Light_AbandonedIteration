#include "ltpch.h"
#include "TextureRendererProgram.h"

#include "Camera/Camera.h"

#include "Graphics/Shader.h"
#include "Graphics/Buffers.h"
#include "Graphics/VertexLayout.h"

#include "../res/Shaders/TextureShader.h"

#include "Utility/ResourceManager.h"

namespace Light {

	TextureRendererProgram::TextureRendererProgram(unsigned int maxVertices, std::shared_ptr<SharedContext> sharedContext)
		: m_MaxVertices(maxVertices)
	{
		ResourceManager::CreateShader("LT_ENGINE_RESOURCES_TEXTURE_SHADER", LT_ENGINE_RESOURCES_TEXTURE_SHADER_VS, LT_ENGINE_RESOURCES_TEXTURE_SHADER_PS);

		m_Shader = ResourceManager::GetShader("LT_ENGINE_RESOURCES_TEXTURE_SHADER");
		m_VertexBuffer = std::shared_ptr<VertexBuffer>(VertexBuffer::Create(nullptr, sizeof(TextureVertexData), maxVertices, sharedContext));
		m_IndexBuffer = std::shared_ptr<IndexBuffer>(IndexBuffer::Create(nullptr, (maxVertices / 4) * 6, sharedContext));
		m_VertexLayout = std::shared_ptr<VertexLayout>(VertexLayout::Create(m_VertexBuffer, m_Shader, { { "POSITION", VertexElementType::Float3 },
		                                                                                                { "TEXCOORD", VertexElementType::Float2 }}, sharedContext));
	}

	bool TextureRendererProgram::Advance()
	{
		if (m_MapCurrent + 4 >= m_MapEnd)
		{
			LT_ENGINE_WARN("TextureRendererProgram::Advance: 'VertexBuffer' map went beyond 'MaxVertices': {}", m_MaxVertices);
			return false;
		}

		m_MapCurrent += 4;
		m_QuadCount++;
	}

	void TextureRendererProgram::SetCamera(const Camera& camera)
	{
		m_Shader->Bind();
		m_Shader->SetUniformMat4("u_ViewProjection", camera.GetProjection() * camera.GetView());
	}

	void TextureRendererProgram::Map()
	{
		m_QuadCount = 0u;

		m_MapCurrent = (TextureRendererProgram::TextureVertexData*)m_VertexBuffer->Map();
		m_MapEnd = m_MapCurrent + m_MaxVertices;
	}

	void TextureRendererProgram::Bind()
	{
		m_VertexBuffer->UnMap();
		m_Shader->Bind();
		m_VertexLayout->Bind();
		m_VertexBuffer->Bind();
		m_IndexBuffer->Bind();
	}
}