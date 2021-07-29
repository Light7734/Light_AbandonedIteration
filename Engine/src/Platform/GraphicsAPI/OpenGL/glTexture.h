#pragma once

#include "Graphics/Texture.h"

#include "Base/Base.h"

namespace Light {

	class glTexture : public Texture
	{
	private:
		unsigned int m_TextureID;

	public:
		glTexture(unsigned int width, unsigned int height, unsigned int components, unsigned char* pixels);
		~glTexture();

		void Bind(unsigned int slot = 0u) override;
	};

}