#pragma once

class CMaterial;

class CDirectionalLight : public CLight
{
public:
	CDirectionalLight(glm::vec3 direction, glm::vec3 color);

	void Bind(const CMaterial* pMaterial, int index) override;
	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetProjectionMatrix() const;
private:
	glm::vec3 m_vDirection;
};