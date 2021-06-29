#pragma once

#include "Base.h"
#include "Graphics/Texture.h"

namespace Light {

	class glTexture : public Texture
	{
	private:
		unsigned int m_TextureID;
		unsigned int m_ActiveTexture;

	public:
		glTexture(unsigned int width, unsigned int height, unsigned int components, unsigned char* pixels);
		~glTexture();

		void Bind(unsigned int slot = 0) override;
	};

}