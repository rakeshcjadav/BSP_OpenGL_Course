#include"Camera.h"
#include"Viewport.h"
#include"Log.h"
#include<format>
#include"InputDelegator.h"
#include"GLFW/glfw3.h"
#include"Log.h"

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

    // Center of Viewport
    m_dLastXPos = m_pViewport->GetWidth()/2.0;
    m_dLastYPos = m_pViewport->GetHeight()/2.0;
    m_dSensitivity = 0.1;
    m_vEulerAngles = glm::vec3(0.0f, -90.0f, 0.0f);
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

void CCamera::OnMousePos(double xPos, double yPos)
{
    if (!IsMouseButtonDown(0))
        return;
    double xOffset = (xPos - m_dLastXPos) * m_dSensitivity;
    double yOffset = (m_dLastYPos - yPos) * m_dSensitivity;

    m_dLastXPos = xPos;
    m_dLastYPos = yPos;

    m_vEulerAngles.y += xOffset;
    m_vEulerAngles.x += yOffset;

    if (m_vEulerAngles.x > 89.0f)
        m_vEulerAngles.x = 89.0f;
    if (m_vEulerAngles.x < -89.0f)
        m_vEulerAngles.x = -89.0f;

    m_vDirection.x = cos(glm::radians(m_vEulerAngles.y)) * cos(glm::radians(m_vEulerAngles.x));
    m_vDirection.y = sin(glm::radians(m_vEulerAngles.x));
    m_vDirection.z = sin(glm::radians(m_vEulerAngles.y)) * cos(glm::radians(m_vEulerAngles.x));
    m_vDirection = glm::normalize(m_vDirection);

    glm::vec3 right = glm::cross(m_vDirection, glm::vec3(0.0f, 1.0f, 0.0f));
    m_vUp = glm::cross(right, m_vDirection);
}

void CCamera::OnMouseScroll(double xOffset, double yOffset)
{
    m_fFOV -= (float)yOffset;
    if (m_fFOV < 1.0f)
        m_fFOV = 1.0f;
    if (m_fFOV > 90.0f)
        m_fFOV = 90;
}

bool CCamera::IsMouseButtonDown(int button)
{
    return m_pDelegator->IsMouseButtonDown(button);
}

void CCamera::OnLeftMouseButtonDown(int mod)
{
    GetMousePos(m_dLastXPos, m_dLastYPos);
}

void CCamera::OnLeftMouseButtonUp(int mod)
{

}

void CCamera::OnRightMouseButtonDown(int mod)
{

}

void CCamera::OnRightMouseButtonUp(int mod)
{

}

void CCamera::OnMiddleMouseButtonDown(int mod)
{

}

void CCamera::OnMiddleMouseButtonUp(int mod)
{

}

void CCamera::GetMousePos(double& xPos, double& yPos)
{
    m_pDelegator->GetMousePos(xPos, yPos);
}
