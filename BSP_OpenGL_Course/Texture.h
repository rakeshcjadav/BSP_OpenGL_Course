#pragma once

class CTexture
{
public:
	CTexture(unsigned int textureID);
	void Bind(unsigned int textureIndex) const;
	unsigned int GetID() const;
private:
	void Bind() const;
private:
	std::string m_strName;
	unsigned int m_IDTexture;
};