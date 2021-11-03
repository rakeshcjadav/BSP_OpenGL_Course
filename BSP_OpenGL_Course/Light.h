#pragma once

class CMaterialPass;

class CLight
{
public:
	CLight(glm::vec3 color);

	virtual void Bind(const CMaterialPass* pPass, int index) = 0;

protected:
	glm::vec3 GetColor() const;
	glm::vec3 m_vColor;
};