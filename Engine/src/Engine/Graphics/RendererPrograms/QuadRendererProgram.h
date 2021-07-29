#pragma once

#include "RendererProgram.h"

#include "Base/Base.h"

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
		Ref<Shader> m_Shader;
		Ref<VertexBuffer> m_VertexBuffer;
		Ref<IndexBuffer> m_IndexBuffer;
		Ref<VertexLayout> m_VertexLayout;

		QuadVertexData* m_MapCurrent = nullptr;
		QuadVertexData* m_MapEnd = nullptr;

		unsigned int m_QuadCount = 0u;
		unsigned int m_MaxVertices = 0u;

	public:
		QuadRendererProgram(unsigned int maxVertices, Ref<SharedContext> sharedContext);

		bool Advance();

		void Map() override;
		void UnMap() override;

		void Bind() override;

		inline QuadVertexData* GetMapCurrent() { return m_MapCurrent; }
		inline unsigned int GetQuadCount() const { return m_QuadCount; }
		inline constexpr unsigned int GetVertexSize() const { return sizeof(QuadVertexData); }
	};

}