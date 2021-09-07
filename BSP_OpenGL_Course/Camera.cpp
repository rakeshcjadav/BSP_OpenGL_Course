#include"Camera.h"
#include"Viewport.h"
#include"Log.h"
#include"InputDelegator.h"
#include"GLFW/glfw3.h"

CCamera::CCamera(const SCameraDef * pCameraDef, const CViewport* pViewport)
{
    m_vPosition = pCameraDef->position;
    m_vDirection = pCameraDef->direction;
    m_vUp = pCameraDef->up;
    m_fFOV = pCameraDef->fov;
    m_fNearPlane = pCameraDef->fNearPlane;
    m_fFarPlane = pCameraDef->fFarPlane;
    m_pViewport = pViewport;
}

void CCamera::SetPosition(glm::vec3 vPos)
{
    m_vPosition = vPos;
}

glm::vec3 CCamera::GetPosition() const
{
    return m_vPosition;
}

void CCamera::SetDirection(glm::vec3 vDirection)
{
    m_vDirection = vDirection;
}

glm::vec3 CCamera::GetDirection() const
{
    return m_vDirection;
}

void CCamera::SetUp(glm::vec3 vUp)
{
    m_vUp = vUp;
}

glm::vec3 CCamera::GetUp() const
{
    return m_vUp;
}

void CCamera::SetFOV(float fov)
{
    m_fFOV = fov;
}

float CCamera::GetFOV() const
{
    return m_fFOV;
}

int CCamera::GetWidth() const
{
    return m_pViewport->GetWidth();
}

int CCamera::GetHeight() const
{
    return m_pViewport->GetHeight();
}

glm::mat4 CCamera::GetViewMatrix()
{
    return glm::lookAt(m_vPosition, m_vPosition+m_vDirection, m_vUp);
}

glm::mat4 CCamera::GetProjectionMatrix()
{
    return glm::perspective(glm::radians(m_fFOV), m_pViewport->GetAspectRatio(), m_fNearPlane, m_fFarPlane);
}
