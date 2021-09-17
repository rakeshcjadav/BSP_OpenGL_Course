#include"Texture.h"
#include"OpenGL.h"
#include"WinUtils.h"
#include"STB.h"
#include"Log.h"

CTexture::CTexture(std::string strTextureFile)
{
    int width, height, format;
    unsigned char* data = LoadTexture(strTextureFile, width, height, format);

	glGenTextures(1, &m_IDTexture);
	glBindTexture(GL_TEXTURE_2D, m_IDTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data); // 24 bits 

    // Texture wrapping : Default mode : REPEAT in both directions
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glGenerateMipmap(GL_TEXTURE_2D);

    // Tri-Linear filters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    stbi_image_free(data);
}

void CTexture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, m_IDTexture);
}

void CTexture::Bind(unsigned int textureIndex)
{
    glActiveTexture(GL_TEXTURE0 + textureIndex);
    Bind();
}

unsigned char* CTexture::LoadTexture(std::string strTextureFile, int & width, int & height, int & format)
{
    int nrChannels;
    std::string filePath = GetTexturesPath() + strTextureFile;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);

    if (data == nullptr)
    {
        std::cout << "Failed to load texture: " << filePath;
        return 0;
    }

    std::cout << "Texture loaded successfully: "<< filePath;
    std::cout << "Width: " << width << " Height: " << height << " Channels: "<< nrChannels;

    format = GL_RGB;
    if (nrChannels > 3)
        format = GL_RGBA;

    return data;
}