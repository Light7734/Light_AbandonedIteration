#include "ltpch.h"
#include "Renderer.h"

#include "Blender.h"
#include "Buffers.h"
#include "Framebuffer.h"
#include "RenderCommand.h"
#include "Texture.h"

#include "Camera/Camera.h"

#include "Events/WindowEvents.h"

#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Light {

	Renderer* Renderer::s_Context = nullptr;

	Renderer::Renderer(GLFWwindow* windowHandle, Ref<SharedContext> sharedContext)
		: m_QuadRenderer(LT_MAX_QUAD_RENDERER_VERTICES, sharedContext),
		  m_TextureRenderer(LT_MAX_TEXTURE_RENDERER_VERTICES, sharedContext),
		  m_ViewProjectionBuffer(nullptr),
		  m_RenderCommand(nullptr),
		  m_Blender(nullptr),
		  m_Camera(nullptr),
		  m_TargetFramebuffer(nullptr)
	{
		LT_ENGINE_ASSERT(!s_Context, "Renderer::Renderer: an instance of 'Renderer' already exists, do not construct this class!");
		s_Context = this;

		m_ViewProjectionBuffer = ConstantBuffer::Create(ConstantBufferIndex::ViewProjection, sizeof(glm::mat4), sharedContext);

		m_RenderCommand = RenderCommand::Create(windowHandle, sharedContext);
		m_Blender = Blender::Create(sharedContext);
	}

	Scope<Renderer> Renderer::Create(GLFWwindow* windowHandle, Ref<SharedContext> sharedContext)
	{
		return MakeScope<Renderer>(new Renderer(windowHandle, sharedContext));
	}

	void Renderer::OnWindowResize(const WindowResizedEvent& event)
	{
		m_RenderCommand->SetViewport(0u, 0u, event.GetSize().x, event.GetSize().y);
	}

	//======================================== DRAW_QUAD_TINT ========================================//
	void Renderer::DrawQuadImpl(const glm::vec3& position, const glm::vec2& size, const glm::vec4& tint)
	{
		// locals
		QuadRendererProgram::QuadVertexData* bufferMap = m_QuadRenderer.GetMapCurrent();

		const float xMin = position.x;
		const float yMin = position.y;
		const float xMax = position.x + size.x;
		const float yMax = position.y + size.y;

		// top left
		bufferMap[0].position = { xMin, yMin, position.z };
		bufferMap[0].tint = tint;

		// top right
		bufferMap[1].position = { xMax, yMin, position.z };
		bufferMap[1].tint = tint;

		// bottom right
		bufferMap[2].position = { xMax, yMax, position.z };
		bufferMap[2].tint = tint;

		// bottom left
		bufferMap[3].position = { xMin, yMax, position.z };
		bufferMap[3].tint = tint;

		// advance
		if (!m_QuadRenderer.Advance())
		{
			LT_ENGINE_WARN("Renderer::DrawQuadImpl: exceeded LT_MAX_QUAD_RENDERER_VERTICES: {}", LT_MAX_QUAD_RENDERER_VERTICES);
			FlushScene();
		}
	}
	//======================================== DRAW_QUAD_TINT ========================================//

	//============================== DRAW_QUAD_TEXTURE ==============================//
	void Renderer::DrawQuadImpl(const glm::vec3& position, const glm::vec2& size, Ref<Texture> texture)
	{
		// #todo: implement a proper binding
		texture->Bind();

		// locals
		TextureRendererProgram::TextureVertexData* bufferMap = m_TextureRenderer.GetMapCurrent();

		const float xMin = position.x;
		const float yMin = position.y;
		const float xMax = position.x + size.x;
		const float yMax = position.y + size.y;

		// top left
		bufferMap[0].position = { xMin, yMin, position.z };
		bufferMap[0].texcoord = { 0.0f, 0.0f };

		// top right
		bufferMap[1].position = { xMax, yMin, position.z };
		bufferMap[1].texcoord = { 1.0f, 0.0f };

		// bottom right
		bufferMap[2].position = { xMax, yMax, position.z };
		bufferMap[2].texcoord = { 1.0f, 1.0f };

		// bottom left
		bufferMap[3].position = { xMin, yMax, position.z };
		bufferMap[3].texcoord = { 0.0f, 1.0f };

		// advance
		if (!m_TextureRenderer.Advance())
		{
			LT_ENGINE_WARN("Renderer::DrawQuadImpl: exceeded LT_MAX_TEXTURE_RENDERER_VERTICES: {}", LT_MAX_TEXTURE_RENDERER_VERTICES);
			FlushScene();
		}
	}
	//============================== DRAW_QUAD_TEXTURE ==============================//

	void Renderer::BeginFrame()
	{
	}

	void Renderer::EndFrame()
	{
		m_RenderCommand->SwapBuffers();
		m_RenderCommand->ClearBackBuffer(m_Camera->GetClearColor());
	}

	void Renderer::BeginSceneImpl(const Ref<Camera>& camera, const Ref<Framebuffer>& targetFrameBuffer /* = nullptr */)
	{
		// determine the target frame buffer
		m_TargetFramebuffer = targetFrameBuffer;

		if (targetFrameBuffer)
			targetFrameBuffer->BindAsTarget();
		else
			m_RenderCommand->DefaultTargetFramebuffer();

		// update view projection buffer
		m_Camera = camera;
		glm::mat4* map = (glm::mat4*)m_ViewProjectionBuffer->Map();
		map[0] = m_Camera->GetProjection() * m_Camera->GetView();
		m_ViewProjectionBuffer->UnMap();

		// map renderers
		m_QuadRenderer.Map();
		m_TextureRenderer.Map();
	}

	void Renderer::FlushScene()
	{
		EndScene();

		m_QuadRenderer.Map();
		m_TextureRenderer.Map();
	}

	void Renderer::EndSceneImpl()
	{
		// enable blending
		m_Blender->Enable(BlendFactor::SRC_ALPHA, BlendFactor::INVERSE_SRC_ALPHA);

		/* quad renderer */
		m_QuadRenderer.UnMap();
		if (m_QuadRenderer.GetQuadCount())
		{
			m_QuadRenderer.Bind();
			m_RenderCommand->DrawIndexed(m_QuadRenderer.GetQuadCount() * 6u);
		}

		/* text renderer */
		m_TextureRenderer.UnMap();
		if (m_TextureRenderer.GetQuadCount())
		{
			m_TextureRenderer.Bind();
			m_RenderCommand->DrawIndexed(m_TextureRenderer.GetQuadCount() * 6u);
		}

		// reset frame buffer
		if(m_TargetFramebuffer)
		{
			m_TargetFramebuffer = nullptr;
			m_RenderCommand->DefaultTargetFramebuffer();
		}
	}

}