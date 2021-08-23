#include"Camera.h"
#include"Viewport.h"
#include"Log.h"
#include<format>
#include"InputDelegator.h"
#include"GLFW/glfw3.h"

CCamera::CCamera(IInputDelegator* pDelegator, const SCameraDef * pCameraDef, const CViewport* pViewport):
    IInputHandler(pDelegator)
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

glm::mat4 CCamera::GetViewMatrix()
{
   return glm::lookAt(m_vPosition, m_vPosition+m_vDirection, m_vUp);
}

glm::mat4 CCamera::GetProjectionMatrix()
{
    return glm::perspective(glm::radians(m_fFOV), m_pViewport->GetAspectRatio(), m_fNearPlane, m_fFarPlane);
}

void CCamera::OnKeyPressed(int key, int mod)
{
    //LogMessage(std::format("Camera recevied the Key pressed event : {0}, {1}", key, mod));
    if(key == GLFW_KEY_W)
        m_vPosition = m_vPosition + m_vDirection * 1.0f;
    else if (key == GLFW_KEY_S)
        m_vPosition = m_vPosition - m_vDirection * 1.0f;
    else if (key == GLFW_KEY_A)
    {
        glm::vec3 right = glm::normalize(glm::cross(m_vUp, m_vDirection));
        m_vPosition = m_vPosition + right * 1.0f;
    }
    else if (key == GLFW_KEY_D)
    {
        glm::vec3 right = glm::normalize(glm::cross(m_vUp, m_vDirection));
        m_vPosition = m_vPosition - right * 1.0f;
    }
}

void CCamera::OnKeyReleased(int key, int mod)
{
    //LogMessage(std::format("Camera recevied the Key released event : {0}, {1}", key, mod));
}

/*
void CCamera::OnKeyRepeat(int key, int mod)
{

}*/
