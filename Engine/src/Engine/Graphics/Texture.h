#pragma once

#include "Base.h"

namespace Light {

	class SharedContext;

	// #todo: improve textures
	class Texture
	{
	public:	
		static Texture* Create(unsigned int width, unsigned int height, unsigned int components, unsigned char* pixels, std::shared_ptr<SharedContext> sharedContext);

		Texture(const Texture&) = delete;
		Texture& operator=(const Texture&) = delete;

		virtual ~Texture() = default;

		virtual void Bind(unsigned int slot = 0) = 0;

	protected:
		Texture() = default;
	};

}