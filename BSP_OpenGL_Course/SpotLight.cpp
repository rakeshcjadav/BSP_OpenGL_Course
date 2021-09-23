#include"SpotLight.h"
#include"Material.h"
#include<string>

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

void CSpotLight::Bind(CMaterial* pMaterial, int index)
{
  
    pMaterial->SetUniform("spotLight[" + std::to_string(index) + "].position", m_vPosition);
    pMaterial->SetUniform("spotLight[" + std::to_string(index) + "].direction", m_vDirection);
    pMaterial->SetUniform("spotLight[" + std::to_string(index) + "].color", m_vColor);
    pMaterial->SetUniform("spotLight[" + std::to_string(index) + "].attenuation", m_vAttenuation);
    pMaterial->SetUniform("spotLight[" + std::to_string(index) + "].innerAngle", glm::cos(glm::radians(m_fInnerCutOffAngle)));
    pMaterial->SetUniform("spotLight[" + std::to_string(index) + "].outerAngle", glm::cos(glm::radians(m_fOuterCutOffAngle)));

}