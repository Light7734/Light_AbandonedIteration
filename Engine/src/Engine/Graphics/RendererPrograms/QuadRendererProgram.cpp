#include "QuadRendererProgram.h"

#include "Camera/Camera.h"

#include "Graphics/Shader.h"
#include "Graphics/Buffers.h"
#include "Graphics/VertexLayout.h"

#include "Utility/ResourceManager.h"

namespace Light {

	QuadRendererProgram::QuadRendererProgram(unsigned int maxVertices, Ref<SharedContext> sharedContext)
		: m_Shader(nullptr),
		  m_IndexBuffer(nullptr),
		  m_VertexLayout(nullptr),
		  m_MapCurrent(nullptr),
		  m_MapEnd(nullptr),
		  m_QuadCount(0u),
		  m_MaxVertices(maxVertices)
	{
		// #todo: don't use relative path
		ResourceManager::LoadShader("LT_ENGINE_RESOURCES_QUAD_SHADER", "Assets/Shaders/Quad/Quad_VS.hlsl", "Assets/Shaders/Quad/Quad_PS.hlsl");

		m_Shader = ResourceManager::GetShader("LT_ENGINE_RESOURCES_QUAD_SHADER");
		m_VertexBuffer = Ref<VertexBuffer>(VertexBuffer::Create(nullptr, sizeof(QuadVertexData), maxVertices, sharedContext));
		m_IndexBuffer = Ref<IndexBuffer>(IndexBuffer::Create(nullptr, (maxVertices / 4) * 6, sharedContext));
		m_VertexLayout = Ref<VertexLayout>(VertexLayout::Create(m_VertexBuffer, m_Shader, { { "POSITION", VertexElementType::Float4 },
		                                                                                    { "COLOR"   , VertexElementType::Float4 }}, sharedContext));
	}

	bool QuadRendererProgram::Advance()
	{
		m_MapCurrent += 4;

		if (m_MapCurrent >= m_MapEnd)
		{
			LT_ENGINE_WARN("QuadRendererProgram::Advance: 'VertexBuffer' map went beyond 'MaxVertices': {}", m_MaxVertices);
			return false;
		}

		m_QuadCount++;
		return true;
	}

	void QuadRendererProgram::Map()
	{
		m_QuadCount = 0u;

		m_MapCurrent = (QuadRendererProgram::QuadVertexData*)m_VertexBuffer->Map();
		m_MapEnd = m_MapCurrent + m_MaxVertices;
	}

	void QuadRendererProgram::UnMap()
	{
		m_VertexBuffer->UnMap();
	}

	void QuadRendererProgram::Bind()
	{
		m_Shader->Bind();
		m_VertexLayout->Bind();
		m_VertexBuffer->Bind();
		m_IndexBuffer->Bind();
	}

}