#pragma once
#include "Light.h"

class CSpotLight : public CLight
{
public:
	CSpotLight(glm::vec3 position, glm::vec3 direction, glm::vec3 color, glm::vec3 atten, float innterAngle, float outerAngle);

	void Bind(const CMaterialPass* pPass, int index) override;
	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetProjectionMatrix() const;
private:
	glm::vec3 m_vPosition;
	glm::vec3 m_vDirection;
	glm::vec3 m_vAttenuation;
	float m_fInnerCutOffAngle;
	float m_fOuterCutOffAngle;
};