#pragma once

#include "Base.h"

#include "RendererPrograms/QuadRendererProgram.h"
#include "RendererPrograms/TextureRendererProgram.h"

#define LT_MAX_QUAD_RENDERER_VERTICES    1028u * 4u
#define LT_MAX_TEXTURE_RENDERER_VERTICES 1028u * 4u

struct GLFWwindow;

namespace Light {

	class RenderCommand;
	class Texture;

	class Camera;

	class SharedContext;

	class Renderer
	{
	private:
		static Renderer* s_Context;

		QuadRendererProgram m_QuadRenderer;
		TextureRendererProgram m_TextureRenderer;

		std::unique_ptr<RenderCommand> m_RenderCommand;

	public:
		static Renderer* Create(GLFWwindow* windowHandle, std::shared_ptr<SharedContext> sharedContext);
		
		static inline void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& tint) { s_Context->DrawQuadImpl(position, size, tint); }
		static inline void DrawQuad(const glm::vec3& position, const glm::vec2& size, std::shared_ptr<Texture> texture) { s_Context->DrawQuadImpl(position, size, texture); }

		static inline void BeginScene(const Camera& camera) { s_Context->BeginSceneImpl(camera); }
		static inline void EndScene() { s_Context->EndSceneImpl(); }

		void BeginFrame();
		void EndFrame();

	private:
		Renderer(GLFWwindow* windowHandle, std::shared_ptr<SharedContext> sharedContext);

		void DrawQuadImpl(const glm::vec3& position, const glm::vec2& size, const glm::vec4& tint);
		void DrawQuadImpl(const glm::vec3& position, const glm::vec2& size, std::shared_ptr<Texture> texture);

		void BeginSceneImpl(const Camera& camera);
		void EndSceneImpl();
	};

}