#include "ltpch.h"
#include "Renderer.h"

#include "GraphicsContext.h"

#include "RenderCommand.h"

namespace Light {

	Renderer* Renderer::m_Context;

	Renderer::Renderer(std::shared_ptr<RenderCommand> renderCommand, void* sharedContext)
		: m_RenderCommand(renderCommand), m_SharedContext(sharedContext)
	{
		m_Context = this;

		m_Shader = std::unique_ptr<Shader>(Shader::Create("res/vertex.vertex", "res/fragment.fragment", m_SharedContext));

		float vertices[] =
		{
			 0.0f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
			-0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
		};

		m_VertexBuffer = std::unique_ptr<VertexBuffer>(VertexBuffer::Create(6 * sizeof(float), (2 + 4) * 3, vertices, m_SharedContext));
		m_VertexLayout = std::unique_ptr<VertexLayout>(VertexLayout::Create(m_VertexBuffer.get(), m_Shader.get(), { { "POSITION", VertexElementType::Float2 },{ "COLOR", VertexElementType::Float4 } }, m_SharedContext));
	}

	Renderer* Renderer::Create(std::shared_ptr<RenderCommand> renderCommand, void* sharedContext)
	{
		return new Renderer(renderCommand, sharedContext);
	}

	void Renderer::Draw()
	{
		m_Shader->Bind();
		m_VertexBuffer->Bind();
		m_VertexLayout->Bind();

		m_RenderCommand->Draw(3u);
	}


}