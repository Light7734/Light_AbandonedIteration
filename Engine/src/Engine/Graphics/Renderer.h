#pragma once

#include "Base.h"

#include "Shader.h"
#include "Buffers.h"
#include "VertexLayout.h"

#include <glm/glm.hpp>

#include <memory>

#define LT_MAX_QUAD 124

namespace Light {

	class RenderCommand;
	class SharedContext;

	class Texture;

	struct RendererProgram
	{
		virtual void Map() = 0;
		virtual void Bind() = 0;
	};

	class Renderer
	{
	private:
		struct QuadRendererProgram : RendererProgram
		{
			// graphics context
			std::shared_ptr<Shader> shader;
			std::shared_ptr<VertexBuffer> vertexBuffer;
			std::shared_ptr<IndexBuffer> indexBuffer;
			std::shared_ptr<VertexLayout> vertexLayout;

			// buffer data
			struct QuadVertexData
			{
				glm::vec3 position;
				glm::vec4 tint;
			};

			QuadVertexData* mapCurrent = nullptr;
			QuadVertexData* mapEnd = nullptr;
			unsigned int quadCount = 0u;

			// functions
			void Map()
			{
				mapCurrent = (QuadVertexData*)vertexBuffer->Map();
				mapEnd = mapCurrent + LT_MAX_QUAD * 4;
			}

			void Bind()
			{
				vertexBuffer->UnMap();
				shader->Bind();
				vertexLayout->Bind();
				vertexBuffer->Bind();
				indexBuffer->Bind();
			}
		};

		struct TextureRendererProgram : public RendererProgram
		{
			// graphics context
			std::shared_ptr<Shader> shader;
			std::shared_ptr<VertexBuffer> vertexBuffer;
			std::shared_ptr<IndexBuffer> indexBuffer;
			std::shared_ptr<VertexLayout> vertexLayout;

			// buffer data
			struct TextureVertexData
			{
				glm::vec3 position;
				glm::vec2 uv;
			};

			TextureVertexData* mapCurrent = nullptr;
			TextureVertexData* mapEnd = nullptr;
			unsigned int quadCount = 0u;

			// functions
			void Map()
			{
				mapCurrent = (TextureVertexData*)vertexBuffer->Map();
				mapEnd = mapCurrent + LT_MAX_QUAD * 4;
			}

			void Bind()
			{
				vertexBuffer->UnMap();
				shader->Bind();
				vertexLayout->Bind();
				vertexBuffer->Bind();
				indexBuffer->Bind();
			}
		};

		static Renderer* s_Context;

		QuadRendererProgram m_QuadRenderer;
		TextureRendererProgram m_TextureRenderer;

		std::shared_ptr<RenderCommand> m_RenderCommand;

		std::shared_ptr<SharedContext> m_SharedContext;

		std::shared_ptr<Texture> m_TestTexture;
	public:
		static Renderer* Create(std::shared_ptr<RenderCommand> renderCommand, std::shared_ptr<SharedContext> sharedContext);
		
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& tint);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, std::shared_ptr<Texture> texture);

		void BeginScene();
		void EndScene();

	private:
		Renderer(std::shared_ptr<RenderCommand> renderCommand, std::shared_ptr<SharedContext> sharedContext);

		void DrawQuadImpl(const glm::vec3& position, const glm::vec2& size, const glm::vec4& tint);
		void DrawQuadImpl(const glm::vec3& position, const glm::vec2& size, std::shared_ptr<Texture> texture);
	};

}