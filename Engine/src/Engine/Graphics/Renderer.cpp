#include "ltpch.h"
#include "Renderer.h"

#include "GraphicsContext.h"

#include "RenderCommand.h"

namespace Light {

	Renderer* Renderer::m_Context;

	Renderer::Renderer(std::shared_ptr<RenderCommand> renderCommand)
		: m_RenderCommand(renderCommand)
	{
		m_Context = this;

		m_Shader = std::unique_ptr<Shader>(Shader::Create("res/vertex.vertex", "res/fragment.fragment"));

//  		m_Shader = std::unique_ptr<Shader>(Shader::Create(
// R"(
// #version 450 core
// 
// layout(location = 0) in vec2 a_Position;
// 
// void main()
// {
// 	gl_Position = vec4(a_Position, 0.0, 1.0);
// })",
// R"(
// #version 450 core
// 
// out vec4 FragColor;
// 
// void main()
// {
// 	FragColor = vec4(1.0, 0.0, 0.0, 1.0);
// }
// )"));

		float vertices[] =
		{
			-0.5f, -0.5f,
			 0.5f, -0.5f,
			 0.0f,  0.5f,
		};

		m_VertexBuffer = std::unique_ptr<VertexBuffer>(VertexBuffer::Create(2 * 3, vertices));
		m_VertexLayout = std::unique_ptr<VertexLayout>(VertexLayout::Create(m_VertexBuffer.get(), { VertexElementType::Float2 }));
	}

	Renderer* Renderer::Create(std::shared_ptr<RenderCommand> renderCommand)
	{
		return new Renderer(renderCommand);
	}

	void Renderer::Draw()
	{
		m_Shader->Bind();
		m_VertexBuffer->Bind();
		m_VertexLayout->Bind();
		m_RenderCommand->Draw(3u);
	}


}