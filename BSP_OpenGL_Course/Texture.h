#pragma once
#include<string>

class CTexture
{
public:
	CTexture(unsigned int textureID);
	void Bind(unsigned int textureIndex) const;
private:
	void Bind() const;
private:
	std::string m_strName;
	unsigned int m_IDTexture;
};