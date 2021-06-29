#include "ltpch.h"
#include "Renderer.h"

#include "GraphicsContext.h"

#include "Utility/ResourceManager.h"

#include "../res/Shaders/QuadShader.h"
#include "../res/Shaders/TextureShader.h"

#include "RenderCommand.h"

#include "Texture.h"

namespace Light {

	Renderer* Renderer::s_Context;

	Renderer::Renderer(std::shared_ptr<RenderCommand> renderCommand, std::shared_ptr<SharedContext> sharedContext)
		: m_RenderCommand(renderCommand), m_SharedContext(sharedContext)
	{
		s_Context = this;

		ResourceManager::CreateShader("QuadShader", LT_ENGINE_RESOURCES_QUAD_SHADER_VS, LT_ENGINE_RESOURCES_QUAD_SHADER_PS);
		ResourceManager::CreateShader("TextureShader", LT_ENGINE_RESOURCES_TEXTURE_SHADER_VS, LT_ENGINE_RESOURCES_TEXTURE_SHADER_PS);

		//** quad renderer  **//
		m_QuadRenderer.shader = ResourceManager::GetShader("QuadShader");
		m_QuadRenderer.vertexBuffer = std::unique_ptr<VertexBuffer>(VertexBuffer::Create(nullptr, sizeof(QuadRendererProgram::QuadVertexData), LT_MAX_QUAD * 4, m_SharedContext));
		m_QuadRenderer.indexBuffer = std::unique_ptr<IndexBuffer>(IndexBuffer::Create(nullptr, LT_MAX_QUAD * 6, m_SharedContext));
		m_QuadRenderer.vertexLayout = std::unique_ptr<VertexLayout>(VertexLayout::Create(m_QuadRenderer.vertexBuffer.get(), m_QuadRenderer.shader.get(), { { "POSITION", VertexElementType::Float3 },{ "COLOR", VertexElementType::Float4 } }, m_SharedContext));
		//** quad renderer **//

		//** texture rendererc **//
		m_TextureRenderer.shader = ResourceManager::GetShader("TextureShader");
		m_TextureRenderer.vertexBuffer = std::unique_ptr<VertexBuffer>(VertexBuffer::Create(nullptr, sizeof(TextureRendererProgram::TextureVertexData), LT_MAX_QUAD * 4, m_SharedContext));
		m_TextureRenderer.indexBuffer = std::unique_ptr<IndexBuffer>(IndexBuffer::Create(nullptr, LT_MAX_QUAD * 6, m_SharedContext));
		m_TextureRenderer.vertexLayout = std::unique_ptr<VertexLayout>(VertexLayout::Create(m_TextureRenderer.vertexBuffer.get(), m_TextureRenderer.shader.get(), { { "POSITION", VertexElementType::Float3 },{ "UV", VertexElementType::Float2 } }, m_SharedContext));
		//** texture rendererc **//
	}

	Renderer* Renderer::Create(std::shared_ptr<RenderCommand> renderCommand, std::shared_ptr<SharedContext> sharedContext)
	{
		return new Renderer(renderCommand, sharedContext);
	}

	void Renderer::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& tint)
	{
		s_Context->DrawQuadImpl(position, size, tint);
	}

	void Renderer::DrawQuad(const glm::vec3& position, const glm::vec2& size, std::shared_ptr<Texture> texture)
	{
		s_Context->DrawQuadImpl(position, size, texture);
	}

	void Renderer::DrawQuadImpl(const glm::vec3& position, const glm::vec2& size, const glm::vec4& tint)
	{
		// check
		if (m_QuadRenderer.mapCurrent + 4 >= m_QuadRenderer.mapEnd)
		{
			LT_ENGINE_WARN("Render::DrawQuad: max calls per frame exceeded the limit: {}", LT_MAX_QUAD);

			EndScene();
			m_QuadRenderer.Map();
		}

		// locals
		const float xMin = position.x;
		const float yMin = position.y;
		const float xMax = position.x + size.x;
		const float yMax = position.y + size.y;

		// TOP_LEFT
		m_QuadRenderer.mapCurrent[0].position = { xMin, yMin, position.z };
		m_QuadRenderer.mapCurrent[0].tint = tint;

		// TOP_RIGHT
		m_QuadRenderer.mapCurrent[1].position = { xMax, yMin, position.z };
		m_QuadRenderer.mapCurrent[1].tint = tint;

		// BOTTOM_RIGHT
		m_QuadRenderer.mapCurrent[2].position = { xMax, yMax, position.z };
		m_QuadRenderer.mapCurrent[2].tint = tint;

		// BOTTOM_LEFT
		m_QuadRenderer.mapCurrent[3].position = { xMin, yMax, position.z };
		m_QuadRenderer.mapCurrent[3].tint = tint;

		// advance
		m_QuadRenderer.mapCurrent += 4;
		m_QuadRenderer.quadCount++;
	}

	void Renderer::DrawQuadImpl(const glm::vec3& position, const glm::vec2& size, std::shared_ptr<Texture> texture)
	{
		// check
		if (m_TextureRenderer.mapCurrent + 4 >= m_TextureRenderer.mapEnd)
		{
			LT_ENGINE_WARN("Render::DrawQuad(Texture): max calls per frame exceeded the limit: {}", LT_MAX_QUAD);

			EndScene();
			m_TextureRenderer.Map();
		}

		// #todo: implement a proper binding
		texture->Bind();

		// locals
		const float xMin = position.x;
		const float yMin = position.y;
		const float xMax = position.x + size.x;
		const float yMax = position.y + size.y;

		// TOP_LEFT
		m_TextureRenderer.mapCurrent[0].position = { xMin, yMin, position.z };
		m_TextureRenderer.mapCurrent[0].uv = { 0, 0 };

		// TOP_RIGHT
		m_TextureRenderer.mapCurrent[1].position = { xMax, yMin, position.z };
		m_TextureRenderer.mapCurrent[1].uv = { 1, 0 };

		// BOTTOM_RIGHT
		m_TextureRenderer.mapCurrent[2].position = { xMax, yMax, position.z };
		m_TextureRenderer.mapCurrent[2].uv = { 1, 1 };

		// BOTTOM_LEFT
		m_TextureRenderer.mapCurrent[3].position = { xMin, yMax, position.z };
		m_TextureRenderer.mapCurrent[3].uv = { 0, 1 };

		// advance
		m_TextureRenderer.mapCurrent += 4;
		m_TextureRenderer.quadCount++;
	}

	void Renderer::BeginScene()
	{
		m_QuadRenderer.Map();
		m_TextureRenderer.Map();
	}

	void Renderer::EndScene()
	{
		if (m_QuadRenderer.quadCount)
		{
			m_QuadRenderer.Bind();

			m_RenderCommand->DrawIndexed(m_QuadRenderer.quadCount * 6);
			m_QuadRenderer.quadCount = 0;
		}

		if (m_TextureRenderer.quadCount)
		{
			m_TextureRenderer.Bind();
			
			m_RenderCommand->DrawIndexed(m_TextureRenderer.quadCount * 6);
			m_TextureRenderer.quadCount = 0;
		}
	}

}