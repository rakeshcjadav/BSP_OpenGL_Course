#include"pch.h"
#include"Transform.h"

CTransform::CTransform(glm::vec3 pos, glm::vec3 rotation, glm::vec3 scale)
{
    m_vPosition = pos;
    m_vRotation = rotation;
    m_vScale = scale;
}

void CTransform::SetPosition(glm::vec3 pos)
{
    m_vPosition = pos;
}

void CTransform::SetRotation(glm::vec3 rotation)
{
    m_vRotation = rotation;
}

void CTransform::SetScale(glm::vec3 scale)
{
    m_vScale = scale;
}

glm::mat4 CTransform::GetTransform() const
{
    // Order : Scale -> Rotate -> Translate
    glm::mat4 transformMat = 
          glm::translate(glm::identity<glm::mat4>(), m_vPosition)
        * glm::toMat4(glm::quat(glm::radians(m_vRotation)))
        * glm::scale(glm::identity<glm::mat4>(), m_vScale);
    return transformMat;
}

void CTransform::Update()
{

}