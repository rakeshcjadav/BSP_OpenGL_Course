#include"CameraController.h"
#include"Camera.h"
#include<format>
#include"InputDelegator.h"
#include"GLFW/glfw3.h"
#include"Log.h"


CCameraController::CCameraController(IInputDelegator* pDelegator, CCamera* pCamera):
    IInputHandler(pDelegator)
{
    m_pCamera = pCamera;

    // Center of Viewport
    //m_dLastXPos = m_pViewport->GetWidth() / 2.0;
    //m_dLastYPos = m_pViewport->GetHeight() / 2.0;
    m_dSensitivity = 0.1;
    m_vEulerAngles = glm::vec3(0.0f, -90.0f, 0.0f);
}

void CCameraController::OnKeyPressed(int key, int mod)
{
    //LogMessage(std::format("Camera recevied the Key pressed event : {0}, {1}", key, mod));
    glm::vec3 pos = m_pCamera->GetPosition();
    glm::vec3 direction = m_pCamera->GetDirection();
    glm::vec3 up = m_pCamera->GetUp();

    if (key == GLFW_KEY_W)
    {
        m_pCamera->SetPosition(pos + direction * 1.0f);
    }
    else if (key == GLFW_KEY_S)
    {
        m_pCamera->SetPosition(pos - direction * 1.0f);
    }
    else if (key == GLFW_KEY_A)
    {
        glm::vec3 right = glm::normalize(glm::cross(up, direction));
        m_pCamera->SetPosition(pos + right * 1.0f);
    }
    else if (key == GLFW_KEY_D)
    {
        glm::vec3 right = glm::normalize(glm::cross(up, direction));
        m_pCamera->SetPosition(pos - right * 1.0f);
    }
}

void CCameraController::OnKeyReleased(int key, int mod)
{
    //LogMessage(std::format("Camera recevied the Key released event : {0}, {1}", key, mod));
}

/*
void CCameraController::OnKeyRepeat(int key, int mod)
{

}*/

void CCameraController::OnMousePos(double xPos, double yPos)
{
    if (!IsMouseButtonDown(0))
        return;
    double xOffset = (xPos - m_dLastXPos) * m_dSensitivity;
    double yOffset = (m_dLastYPos - yPos) * m_dSensitivity;

    m_dLastXPos = xPos;
    m_dLastYPos = yPos;

    m_vEulerAngles.y += (float)xOffset;
    m_vEulerAngles.x += (float)yOffset;

    if (m_vEulerAngles.x > 89.0f)
        m_vEulerAngles.x = 89.0f;
    if (m_vEulerAngles.x < -89.0f)
        m_vEulerAngles.x = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(m_vEulerAngles.y)) * cos(glm::radians(m_vEulerAngles.x));
    direction.y = sin(glm::radians(m_vEulerAngles.x));
    direction.z = sin(glm::radians(m_vEulerAngles.y)) * cos(glm::radians(m_vEulerAngles.x));
    direction = glm::normalize(direction);
    m_pCamera->SetDirection(direction);

    glm::vec3 right = glm::cross(direction, glm::vec3(0.0f, 1.0f, 0.0f));
    m_pCamera->SetUp(glm::cross(right, direction));
}

void CCameraController::OnMouseScroll(double xOffset, double yOffset)
{
    float fov = m_pCamera->GetFOV();
    fov -= (float)yOffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 90.0f)
        fov = 90;
    m_pCamera->SetFOV(fov);
}

bool CCameraController::IsMouseButtonDown(int button)
{
    return m_pDelegator->IsMouseButtonDown(button);
}

void CCameraController::OnLeftMouseButtonDown(int mod)
{
    GetMousePos(m_dLastXPos, m_dLastYPos);
}

void CCameraController::OnLeftMouseButtonUp(int mod)
{

}

void CCameraController::OnRightMouseButtonDown(int mod)
{

}

void CCameraController::OnRightMouseButtonUp(int mod)
{

}

void CCameraController::OnMiddleMouseButtonDown(int mod)
{

}

void CCameraController::OnMiddleMouseButtonUp(int mod)
{

}

void CCameraController::GetMousePos(double& xPos, double& yPos)
{
    m_pDelegator->GetMousePos(xPos, yPos);
}