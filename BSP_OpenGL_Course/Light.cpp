#include"Light.h"

CLight::CLight(glm::vec3 position, glm::vec3 color)
{
    m_vPosition = position;
    m_vColor = color;
}

glm::vec3 CLight::GetPosition() const
{
    return m_vPosition;
}

glm::vec3 CLight::GetColor() const
{
    return m_vColor;
}