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

	class TextureRendererProgram : RendererProgram
	{
	private:
		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		std::shared_ptr<VertexLayout> m_VertexLayout;

		struct TextureVertexData; // <-- forward declaration
		TextureVertexData* m_MapCurrent = nullptr;
		TextureVertexData* m_MapEnd = nullptr;

		unsigned int m_QuadCount = 0u;
		unsigned int m_MaxVertices = 0u;

	public:
		struct TextureVertexData
		{
			glm::vec3 position;
			glm::vec2 texcoord;
		};

		TextureRendererProgram(unsigned int maxVertices, std::shared_ptr<SharedContext> sharedContext);

		bool Advance();

		void SetCamera(const Camera& camera) override;

		void Map() override;
		void Bind() override;

		inline TextureVertexData* GetMapCurrent() { return m_MapCurrent; }
		inline unsigned int GetQuadCount() const { return m_QuadCount; }
		inline constexpr unsigned int GetVertexSize() const { return sizeof(TextureVertexData); }
	};

}