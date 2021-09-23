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

void CSpotLight::Bind(CMaterial* pMaterial)
{
    pMaterial->SetUniform("spotLight.position", m_vPosition);
    pMaterial->SetUniform("spotLight.direction", m_vDirection);
    pMaterial->SetUniform("spotLight.color", m_vColor);
    pMaterial->SetUniform("spotLight.attenuation", m_vAttenuation);
    pMaterial->SetUniform("spotLight.innerAngle", glm::cos(glm::radians(m_fInnerCutOffAngle)));
    pMaterial->SetUniform("spotLight.outerAngle", glm::cos(glm::radians(m_fOuterCutOffAngle)));

}