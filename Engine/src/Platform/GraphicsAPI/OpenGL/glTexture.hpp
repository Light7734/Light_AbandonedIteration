#pragma once

#include "Base/Base.hpp"
#include "Graphics/Texture.hpp"

namespace Light {

class glTexture: public Texture
{
private:
	unsigned int m_TextureID;

public:
	glTexture(unsigned int width, unsigned int height, unsigned int components, unsigned char* pixels, const std::string& filePath);
	~glTexture();

	void Bind(unsigned int slot = 0u) override;

	void* GetTexture() override;
};

} // namespace Light
