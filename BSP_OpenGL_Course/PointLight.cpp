#include"pch.h"
#include"PointLight.h"
#include"Material.h"

CPointLight::CPointLight(glm::vec3 position, glm::vec3 color, glm::vec3 attenuation):
    m_vPosition(0.0f),
    m_vAttenuation(0.0f),
    CLight(color)
{
    m_vPosition = position;
    m_vAttenuation = attenuation;
}

void CPointLight::Bind(const CMaterial* pMaterial, int index)
{
    pMaterial->SetUniform("pointLight[" + std::to_string(index) + "].position", m_vPosition);
    pMaterial->SetUniform("pointLight[" + std::to_string(index) + "].color", m_vColor);
    pMaterial->SetUniform("pointLight[" + std::to_string(index) + "].attenuation", m_vAttenuation);
}