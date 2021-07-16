#include "ltpch.h"
#include "glFramebuffer.h"

#include <glm/glm.hpp>

#include <glad/glad.h>

namespace Light {

	glFramebuffer::glFramebuffer(const FramebufferSpecification& specification)
		: m_Specification(specification), m_BufferID(0u), m_ColorAttachment(0u), m_DepthStencilAttachment(0u)
	{
		Resize({ specification.width, specification.height });
	}

	glFramebuffer::~glFramebuffer()
	{
		glDeleteFramebuffers(1, &m_BufferID);
		glDeleteTextures(1, &m_ColorAttachment);
		// glDeleteTextures(1, &m_DepthStencilAttachment);
	}

	void glFramebuffer::BindAsTarget()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_BufferID);
		glViewport(0, 0, m_Specification.width, m_Specification.height);

		glClearColor(m_Specification.defaultColor.r, m_Specification.defaultColor.g, m_Specification.defaultColor.b, m_Specification.defaultColor.a);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void glFramebuffer::BindAsResource()
	{
		LT_ENGINE_ERROR("glFramebuffer::BindAsResource: NO_IMPLEMENT!");
	}

	void glFramebuffer::Resize(const glm::vec2& size)
	{
		if (m_BufferID)
		{
			glDeleteFramebuffers(1, &m_BufferID);
			glDeleteTextures(1, &m_ColorAttachment);
			// glDeleteTextures(1, &m_DepthStencilAttachment);
		}

		glCreateFramebuffers(1, &m_BufferID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_BufferID);

		// create color attachment
		glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachment);
		glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Specification.width, m_Specification.height, NULL, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTextureParameteri(m_ColorAttachment, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_ColorAttachment, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);

		// glTextureStorage2D(m_ColorAttachment, 0, GL_RGBA8, m_Specification.width, m_Specification.height);

	//	glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthStencilAttachment);
	//	glBindTexture(GL_TEXTURE_2D, m_DepthStencilAttachment);
	//	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_Specification.width, m_Specification.height, NULL, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
	//	// glTextureStorage2D(m_DepthStencilAttachment, 0, GL_DEPTH24_STENCIL8, m_Specification.width, m_Specification.height);
	//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthStencilAttachment, 0);

		LT_ENGINE_ASSERT((glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE), "glFramebuffer::Validate: framebuffer is incomplete");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

}