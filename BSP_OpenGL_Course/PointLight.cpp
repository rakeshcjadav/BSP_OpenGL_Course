#include"pch.h"
#include"PointLight.h"
#include"MaterialPass.h"

CPointLight::CPointLight(glm::vec3 position, glm::vec3 color, glm::vec3 attenuation):
	m_vPosition(0.0f),
	m_vAttenuation(0.0f),
	CLight(color)
{
	m_vPosition = position;
	m_vAttenuation = attenuation;
}

void CPointLight::Bind(const CMaterialPass* pPass, int index)
{
	pPass->SetUniform("pointLight[" + std::to_string(index) + "].position", m_vPosition);
	pPass->SetUniform("pointLight[" + std::to_string(index) + "].color", m_vColor);
	pPass->SetUniform("pointLight[" + std::to_string(index) + "].attenuation", m_vAttenuation);
}