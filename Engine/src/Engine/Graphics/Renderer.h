#pragma once

#include "Base.h"

#include "Shader.h"
#include "Buffers.h"
#include "VertexLayout.h"

#include <memory>

namespace Light {

	class RenderCommand;

	class Renderer
	{
	private:
		static Renderer* m_Context;

		std::shared_ptr<RenderCommand> m_RenderCommand;

		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<VertexLayout> m_VertexLayout;

		void* m_SharedContext;
	public:
		static Renderer* Create(std::shared_ptr<RenderCommand> renderCommand, void* sharedContext);
		
		void Draw();

	private:
		Renderer(std::shared_ptr<RenderCommand> renderCommand, void* sharedContext);
	};

}