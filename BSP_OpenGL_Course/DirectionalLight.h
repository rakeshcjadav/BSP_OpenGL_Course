#pragma once
#include "Light.h"

class CDirectionalLight : public CLight
{
public:
	CDirectionalLight(glm::vec3 direction, glm::vec3 color);

	void Bind(const CMaterialPass* pPass, int index) override;
	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetProjectionMatrix() const;
private:
	glm::vec3 m_vDirection;
};