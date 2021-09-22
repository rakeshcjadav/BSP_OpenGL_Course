#include"Light.h"

CLight::CLight(glm::vec3 color)
{
    m_vColor = color;
}

glm::vec3 CLight::GetColor() const
{
    return m_vColor;
}