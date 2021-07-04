#include "ltpch.h"
#include "Renderer.h"

#include "RenderCommand.h"
#include "Texture.h"

namespace Light {

	Renderer* Renderer::s_Context = nullptr;

	Renderer::Renderer(GLFWwindow* windowHandle, std::shared_ptr<SharedContext> sharedContext)
		: m_QuadRenderer(LT_MAX_QUAD_RENDERER_VERTICES, sharedContext),
		  m_TextureRenderer(LT_MAX_TEXTURE_RENDERER_VERTICES, sharedContext)
	{
		LT_ENGINE_ASSERT(!s_Context, "Renderer::Renderer: an instance of 'Renderer' already exists, do not construct this class!");
		s_Context = this;

		m_RenderCommand = std::unique_ptr<RenderCommand>(RenderCommand::Create(windowHandle, sharedContext));
	}

	Renderer* Renderer::Create(GLFWwindow* windowHandle, std::shared_ptr<SharedContext> sharedContext)
	{
		return new Renderer(windowHandle, sharedContext);
	}

	void Renderer::DrawQuadImpl(const glm::vec3& position, const glm::vec2& size, const glm::vec4& tint)
	{
		// locals
		QuadRendererProgram::QuadVertexData* bufferMap = m_QuadRenderer.GetMapCurrent();

		const float xMin = position.x;
		const float yMin = position.y;
		const float xMax = position.x + size.x;
		const float yMax = position.y + size.y;

		//** TOP_LEFT **//
		bufferMap[0].position = { xMin, yMin, position.z };
		bufferMap[0].tint = tint;

		//** TOP_RIGHT **//
		bufferMap[1].position = { xMax, yMin, position.z };
		bufferMap[1].tint = tint;

		//** BOTTOM_RIGHT **//
		bufferMap[2].position = { xMax, yMax, position.z };
		bufferMap[2].tint = tint;

		//** BOTTOM_LEFT **//
		bufferMap[3].position = { xMin, yMax, position.z };
		bufferMap[3].tint = tint;

		// advance
		if (!m_QuadRenderer.Advance())
		{
			EndFrame();
			BeginFrame();
		}
	}

	void Renderer::DrawQuadImpl(const glm::vec3& position, const glm::vec2& size, std::shared_ptr<Texture> texture)
	{
		// #todo: implement a proper binding
		texture->Bind();

		// locals
		TextureRendererProgram::TextureVertexData* bufferMap = m_TextureRenderer.GetMapCurrent();

		const float xMin = position.x;
		const float yMin = position.y;
		const float xMax = position.x + size.x;
		const float yMax = position.y + size.y;

		//** TOP_LEFT **//
		bufferMap[0].position = { xMin, yMin, position.z };
		bufferMap[0].texcoord = { 0.0f, 0.0f };

		//** TOP_RIGHT **//
		bufferMap[1].position = { xMax, yMin, position.z };
		bufferMap[1].texcoord = { 1.0f, 0.0f };

		//** BOTTOM_RIGHT **//
		bufferMap[2].position = { xMax, yMax, position.z };
		bufferMap[2].texcoord = { 1.0f, 1.0f };

		//** BOTTOM_LEFT **//
		bufferMap[3].position = { xMin, yMax, position.z };
		bufferMap[3].texcoord = { 0.0f, 1.0f };

		// advance
		if (!m_TextureRenderer.Advance())
		{
			EndFrame();
			BeginFrame();
		}
	}

	void Renderer::BeginFrame()
	{

	}

	void Renderer::EndFrame()
	{

	}

	void Renderer::BeginSceneImpl(const Camera& camera)
	{
		m_QuadRenderer.Map();
		m_TextureRenderer.Map();

		m_QuadRenderer.SetCamera(camera);
		m_TextureRenderer.SetCamera(camera);
	}

	void Renderer::EndSceneImpl()
	{
		//** QUAD_RENDERER **//
		if (m_QuadRenderer.GetQuadCount())
		{
			m_QuadRenderer.Bind();
			m_RenderCommand->DrawIndexed(m_QuadRenderer.GetQuadCount() * 6u);
		}

		//** TEXT_RENDERER **//
		if (m_TextureRenderer.GetQuadCount())
		{
			m_TextureRenderer.Bind();
			m_RenderCommand->DrawIndexed(m_TextureRenderer.GetQuadCount() * 6u);
		}

		m_RenderCommand->SwapBuffers();
		m_RenderCommand->ClearBackBuffer();
	}

}