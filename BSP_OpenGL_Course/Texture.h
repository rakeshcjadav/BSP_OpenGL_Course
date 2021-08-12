#pragma once
#include<string>

class CTexture
{
public:
	CTexture(std::string strTextureFile);
	void Bind();
	void Bind(unsigned int textureIndex);
private:
	unsigned char* LoadTexture(std::string strTextureFile, int& width, int& height, int& format);
private:
	unsigned int m_IDTexture;
};