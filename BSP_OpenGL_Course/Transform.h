#pragma once
#include"GLM.h"

class CTransform
{
public:
    CTransform(glm::vec3 pos = glm::zero<glm::vec3>(), glm::vec3 rotation = glm::zero<glm::vec3>(), glm::vec3 scale = glm::one<glm::vec3>());
    void SetPosition(glm::vec3 pos);
    void SetRotation(glm::vec3 rotation);
    void SetScale(glm::vec3 scale);
    glm::mat4 GetTransform() const;

    void Update();

private:
    glm::vec3 m_vPosition;
    glm::vec3 m_vRotation;
    glm::vec3 m_vScale;
};