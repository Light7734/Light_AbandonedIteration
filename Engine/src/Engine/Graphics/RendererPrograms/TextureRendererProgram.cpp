#include "ltpch.h"
#include "TextureRendererProgram.h"

#include "Camera/Camera.h"

#include "Graphics/Shader.h"
#include "Graphics/Buffers.h"
#include "Graphics/VertexLayout.h"

#include "Utility/ResourceManager.h"

namespace Light {

	TextureRendererProgram::TextureRendererProgram(unsigned int maxVertices, Ref<SharedContext> sharedContext)
		: m_MaxVertices(maxVertices)
	{
		ResourceManager::LoadShader("LT_ENGINE_RESOURCES_TEXTURE_SHADER", "../Engine/res/Shaders/Texture/Texture_VS", "../Engine/res/Shaders/Texture/Texture_PS");

		m_Shader = ResourceManager::GetShader("LT_ENGINE_RESOURCES_TEXTURE_SHADER");
		m_VertexBuffer = Ref<VertexBuffer>(VertexBuffer::Create(nullptr, sizeof(TextureVertexData), maxVertices, sharedContext));
		m_IndexBuffer = Ref<IndexBuffer>(IndexBuffer::Create(nullptr, (maxVertices / 4) * 6, sharedContext));
		m_VertexLayout = Ref<VertexLayout>(VertexLayout::Create(m_VertexBuffer, m_Shader, { { "POSITION", VertexElementType::Float3 },
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
		return true;
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

	void TextureRendererProgram::UnMap()
	{
		m_VertexBuffer->UnMap();
	}

	void TextureRendererProgram::Bind()
	{
		m_Shader->Bind();
		m_VertexLayout->Bind();
		m_VertexBuffer->Bind();
		m_IndexBuffer->Bind();
	}
}