#include"pch.h"
#include"SpotLight.h"
#include"Material.h"

CSpotLight::CSpotLight(glm::vec3 position, glm::vec3 direction, glm::vec3 color, glm::vec3 atten, float innterAngle, float outerAngle):
	m_vPosition(0.0f),
	m_vDirection(0.0f),
	m_vAttenuation(0.0f),
	m_fInnerCutOffAngle(0.0f),
	m_fOuterCutOffAngle(0.0f),
	CLight(color)
{
	m_vPosition = position;
	m_vDirection = direction;
	m_vAttenuation = atten;
	m_fInnerCutOffAngle = innterAngle;
	m_fOuterCutOffAngle = outerAngle;
}

void CSpotLight::Bind(const CMaterial* pMaterial, int index)
{
	pMaterial->SetUniform("spotLight[" + std::to_string(index) + "].position", m_vPosition);
	pMaterial->SetUniform("spotLight[" + std::to_string(index) + "].direction", m_vDirection);
	pMaterial->SetUniform("spotLight[" + std::to_string(index) + "].color", m_vColor);
	pMaterial->SetUniform("spotLight[" + std::to_string(index) + "].attenuation", m_vAttenuation);
	pMaterial->SetUniform("spotLight[" + std::to_string(index) + "].innerAngle", glm::cos(glm::radians(m_fInnerCutOffAngle)));
	pMaterial->SetUniform("spotLight[" + std::to_string(index) + "].outerAngle", glm::cos(glm::radians(m_fOuterCutOffAngle)));
	glm::mat4 lightViewMat = GetViewMatrix();
	glm::mat4 lightProjectionMat = GetProjectionMatrix();
	glm::mat4 lightProjectionViewMat = lightProjectionMat * lightViewMat;
	pMaterial->SetUniform("LightProjectionViewMat", lightProjectionViewMat);
}

glm::mat4 CSpotLight::GetViewMatrix() const
{
	return glm::lookAt(m_vPosition, m_vPosition+m_vDirection, glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 CSpotLight::GetProjectionMatrix() const
{
	return glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 20.0f);
}