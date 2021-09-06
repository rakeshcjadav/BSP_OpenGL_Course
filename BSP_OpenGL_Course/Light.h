#pragma once
#include"GLM.h"

class CLight
{
public:
    CLight(glm::vec3 position, glm::vec3 color);

    glm::vec3 GetPosition() const;
    glm::vec3 GetColor() const;
private:
    glm::vec3 m_vPosition;
    glm::vec3 m_vColor;
};