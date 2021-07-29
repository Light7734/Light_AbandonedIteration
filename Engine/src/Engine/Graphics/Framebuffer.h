#pragma once

#include "Base/Base.h"

#include <glm/glm.hpp>

namespace Light {

	class SharedContext;

	struct FramebufferSpecification
	{
		unsigned int width, height;
		unsigned int samples = 1;

		glm::uvec4 defaultColor = glm::uvec4(0u);
	};

	class Framebuffer
	{
	public:
		static Ref<Framebuffer> Create(const FramebufferSpecification& specification, Ref<SharedContext> sharedContext);

		virtual void BindAsTarget() = 0;
		virtual void BindAsResource() = 0;

		virtual void Resize(const glm::uvec2& size) = 0;

		virtual void* GetColorAttachment() = 0;

	protected:
		Framebuffer() = default;
	};

}