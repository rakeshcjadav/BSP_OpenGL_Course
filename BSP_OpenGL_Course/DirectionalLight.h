#pragma once
#include "Light.h"

class CMaterial;

class CDirectionalLight : public CLight
{
public:
    CDirectionalLight(glm::vec3 direction, glm::vec3 color);

    void Bind(CMaterial* pMaterial) override;
private:
    glm::vec3 m_vDirection;
};