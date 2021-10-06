#include"pch.h"
#include"DirectionalLight.h"
#include"Material.h"

CDirectionalLight::CDirectionalLight(glm::vec3 direction, glm::vec3 color) :
	m_vDirection(0.0f),
	CLight(color)
{
	m_vDirection = direction;
}

void CDirectionalLight::Bind(const CMaterial* pMaterial, int index)
{
	pMaterial->SetUniform("directionalLight.direction", m_vDirection);
	pMaterial->SetUniform("directionalLight.color", m_vColor);
}