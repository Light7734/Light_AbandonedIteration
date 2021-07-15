#pragma once

#include "Base.h"
#include "Graphics/Framebuffer.h"

namespace Light {

	class glFramebuffer : public Framebuffer
	{
	private:
		FramebufferSpecification m_Specification;

		unsigned int m_BufferID, m_ColorAttachment, m_DepthStencilAttachment;

	public:
		glFramebuffer(const FramebufferSpecification& specification);
		~glFramebuffer();

		inline void* GetColorAttachment() override { return (void*)m_ColorAttachment; }

		void BindAsTarget() override;
		void BindAsResource() override;
	};

}