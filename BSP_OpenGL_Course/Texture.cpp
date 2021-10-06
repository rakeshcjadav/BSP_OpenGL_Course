#include"pch.h"
#include"Texture.h"

CTexture::CTexture(unsigned int textureID)
{
	m_IDTexture = textureID;
}

void CTexture::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_IDTexture);
}

void CTexture::Bind(unsigned int textureIndex) const
{
	glActiveTexture(GL_TEXTURE0 + textureIndex);
	Bind();
}