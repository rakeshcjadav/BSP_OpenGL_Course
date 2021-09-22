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

void CPointLight::Bind(CMaterial* pMaterial)
{
    pMaterial->SetUniform("pointLight.position", m_vPosition);
    pMaterial->SetUniform("pointLight.color", m_vColor);
    pMaterial->SetUniform("pointLight.attenuation", m_vAttenuation);
}