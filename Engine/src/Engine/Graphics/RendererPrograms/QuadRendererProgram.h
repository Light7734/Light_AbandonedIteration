#pragma once

#include "Base.h"
#include "RendererProgram.h"

#include <glm/glm.hpp>

namespace Light {

	class Shader;
	class VertexBuffer;
	class IndexBuffer;
	class VertexLayout;

	class Camera;

	class SharedContext;

	class QuadRendererProgram : RendererProgram
	{
	public:
		struct QuadVertexData
		{
			glm::vec3 position;
			glm::vec4 tint;
		};

	private:
		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		std::shared_ptr<VertexLayout> m_VertexLayout;

		QuadVertexData* m_MapCurrent = nullptr;
		QuadVertexData* m_MapEnd = nullptr;

		unsigned int m_QuadCount = 0u;
		unsigned int m_MaxVertices = 0u;

	public:
		QuadRendererProgram(unsigned int maxVertices, std::shared_ptr<SharedContext> sharedContext);

		bool Advance();
		
		void SetCamera(const Camera& camera) override;

		void Map() override;
		void UnMap() override;

		void Bind() override;

		inline QuadVertexData* GetMapCurrent() { return m_MapCurrent; }
		inline unsigned int GetQuadCount() const { return m_QuadCount; }
		inline constexpr unsigned int GetVertexSize() const { return sizeof(QuadVertexData); }
	};

}