#pragma once

#include "Base.h"

#include "Buffers.h"
#include "Blender.h"
#include "Framebuffer.h"

#include "RendererPrograms/QuadRendererProgram.h"
#include "RendererPrograms/TextureRendererProgram.h"

#define LT_MAX_QUAD_RENDERER_VERTICES    1028u * 4u
#define LT_MAX_TEXTURE_RENDERER_VERTICES 1028u * 4u

struct GLFWwindow;

namespace Light {

	class RenderCommand;
	class Blender;

	class Framebuffer;

	class Camera;

	class Texture;

	class WindowResizedEvent;

	class SharedContext;

	class Renderer
	{
	private:
		static Renderer* s_Context;
		
		// renderer programs
		QuadRendererProgram m_QuadRenderer;
		TextureRendererProgram m_TextureRenderer;

		// constant buffers
		std::unique_ptr<ConstantBuffer> m_ViewProjectionBuffer;

		std::unique_ptr<RenderCommand> m_RenderCommand;
		std::unique_ptr<Blender> m_Blender;

		std::shared_ptr<Framebuffer> m_TargetFramebuffer;

		std::shared_ptr<Camera> m_Camera;

	public:
		static Renderer* Create(GLFWwindow* windowHandle, std::shared_ptr<SharedContext> sharedContext);
		
		static inline void SetTargetFramebuffer(std::shared_ptr<Framebuffer> framebuffer) { s_Context->SetTargetFramebufferImpl(framebuffer); }

		static inline void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& tint) { s_Context->DrawQuadImpl(position, size, tint); }
		static inline void DrawQuad(const glm::vec3& position, const glm::vec2& size, std::shared_ptr<Texture> texture) { s_Context->DrawQuadImpl(position, size, texture); }

		static inline void BeginScene(const std::shared_ptr<Camera>& camera, const std::shared_ptr<Framebuffer>& targetFrameBuffer = nullptr) { s_Context->BeginSceneImpl(camera, targetFrameBuffer); }
		static inline void EndScene() { s_Context->EndSceneImpl(); }
		
		void OnWindowResize(const WindowResizedEvent& event);

		void BeginFrame();
		void EndFrame();

	private:
		Renderer(GLFWwindow* windowHandle, std::shared_ptr<SharedContext> sharedContext);

		void SetTargetFramebufferImpl(std::shared_ptr<Framebuffer> framebuffer);

		void DrawQuadImpl(const glm::vec3& position, const glm::vec2& size, const glm::vec4& tint);
		void DrawQuadImpl(const glm::vec3& position, const glm::vec2& size, std::shared_ptr<Texture> texture);

		void BeginSceneImpl(const std::shared_ptr<Camera>& camera, const std::shared_ptr<Framebuffer>& targetFrameBuffer = nullptr);
		void FlushScene();
		void EndSceneImpl();
	};

}