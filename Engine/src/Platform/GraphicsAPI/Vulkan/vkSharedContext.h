#pragma once

#include "Base/Base.h"
#include "Graphics/SharedContext.h"

#include <volk.h>

namespace Light {

	class vkSharedContext : public SharedContext
	{
	private:
		friend class vkGraphicsContext;
	private:
		VkDevice m_Device = VK_NULL_HANDLE;

	public:
		inline VkDevice GetDevice() { return m_Device; }
	};

}