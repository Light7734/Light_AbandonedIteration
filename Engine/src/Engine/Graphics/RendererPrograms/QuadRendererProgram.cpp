#include "ltpch.h"
#include "QuadRendererProgram.h"

#include "Camera/Camera.h"

#include "Graphics/Shader.h"
#include "Graphics/Buffers.h"
#include "Graphics/VertexLayout.h"

#include "../res/Shaders/QuadShader.h"

#include "Utility/ResourceManager.h"

namespace Light {

	QuadRendererProgram::QuadRendererProgram(unsigned int maxVertices, std::shared_ptr<SharedContext> sharedContext)
		: m_MaxVertices(maxVertices)
	{
		ResourceManager::CreateShader("LT_ENGINE_RESOURCES_QUAD_SHADER", LT_ENGINE_RESOURCES_QUAD_SHADER_VS, LT_ENGINE_RESOURCES_QUAD_SHADER_PS);

		m_Shader = ResourceManager::GetShader("LT_ENGINE_RESOURCES_QUAD_SHADER");
		m_VertexBuffer = std::shared_ptr<VertexBuffer>(VertexBuffer::Create(nullptr, sizeof(QuadVertexData), maxVertices, sharedContext));
		m_IndexBuffer = std::shared_ptr<IndexBuffer>(IndexBuffer::Create(nullptr, (maxVertices / 4) * 6, sharedContext));
		m_VertexLayout = std::shared_ptr<VertexLayout>(VertexLayout::Create(m_VertexBuffer, m_Shader, { { "POSITION", VertexElementType::Float3 },
		                                                                                                { "COLOR"   , VertexElementType::Float4 }}, sharedContext));
	}

	bool QuadRendererProgram::Advance()
	{
		if (m_MapCurrent + 4 >= m_MapEnd)
		{
			LT_ENGINE_WARN("QuadRendererProgram::Advance: 'VertexBuffer' map went beyond 'MaxVertices': {}", m_MaxVertices);
			return false;
		}

		m_MapCurrent += 4;
		m_QuadCount++;
	}

	void QuadRendererProgram::SetCamera(const Camera& camera)
	{
		m_Shader->Bind();
		m_Shader->SetUniformMat4("u_ViewProjection", camera.GetProjection() * camera.GetView());
	}

	void QuadRendererProgram::Map()
	{
		m_QuadCount = 0u;

		m_MapCurrent = (QuadRendererProgram::QuadVertexData*)m_VertexBuffer->Map();
		m_MapEnd = m_MapCurrent + m_MaxVertices;
	}

	void QuadRendererProgram::Bind()
	{
		m_VertexBuffer->UnMap();
		m_Shader->Bind();
		m_VertexLayout->Bind();
		m_VertexBuffer->Bind();
		m_IndexBuffer->Bind();
	}
}