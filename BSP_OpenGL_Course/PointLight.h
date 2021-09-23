#pragma once
#include "Light.h"

class CMaterial;

class CPointLight : public CLight
{
public:
    CPointLight(glm::vec3 position, glm::vec3 color, glm::vec3 attenuation);

    void Bind(CMaterial* pMaterial, int index) override;
private:
    glm::vec3 m_vPosition;
    glm::vec3 m_vAttenuation;
};