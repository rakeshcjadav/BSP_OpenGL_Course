#include"Texture.h"
#include"OpenGL.h"
#include"WinUtils.h"
#include"AssetManager.h"
#include"Log.h"

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