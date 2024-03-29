#include "glTexture.hpp"

#include <glad/glad.h>

namespace Light {

glTexture::glTexture(unsigned int width, unsigned int height, unsigned int components, unsigned char* pixels, const std::string& filePath)
    : Texture(filePath), m_TextureID(NULL)
{
	// create texture
	glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);

	// set texture parameters
	glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// determine formats
	unsigned int format = components == 4u ? GL_RGBA :
	                      components == 3u ? GL_RGB :
	                      components == 2u ? GL_RG :
	                      components == 1u ? GL_RED :
                                             NULL;

	unsigned int internalFormat = format == GL_RGBA ? GL_RGBA8 :
	                              format == GL_RGB  ? GL_RGB8 :
	                              format == GL_RG   ? GL_RG8 :
	                              format == GL_RED  ? GL_R8 :
                                                      NULL;

	// check
	ASSERT(format, "Invalid number of components: {}", components);


	// #todo: isn't there something like glTextureImage2D ???
	// create texture and mipsmaps
	Bind();
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);
	glGenerateMipmap(GL_TEXTURE_2D);
}

glTexture::~glTexture()
{
	glDeleteTextures(1, &m_TextureID);
}

void glTexture::Bind(unsigned int slot /* = 0u */)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
}

void* glTexture::GetTexture()
{
	return (void*)(intptr_t)m_TextureID;
}

} // namespace Light
