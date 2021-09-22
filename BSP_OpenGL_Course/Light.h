#pragma once
#include"GLM.h"

class CMaterial;

class CLight
{
public:
    CLight(glm::vec3 color);

    virtual void Bind(CMaterial* pMaterial) = 0;

protected:
    glm::vec3 GetColor() const;
    glm::vec3 m_vColor;
};