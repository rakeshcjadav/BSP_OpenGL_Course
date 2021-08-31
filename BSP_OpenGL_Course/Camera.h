#pragma once
#include "GLM.h"
#include "InputHandler.h"

// Forward Declarations
struct SCameraDef;
class CViewport;

class CCamera : public IInputHandler
{
public:
    CCamera(IInputDelegator * pDelegator, const SCameraDef * pCameraDef, const CViewport * pViewport);
    void SetPosition(glm::vec3 vPos);
    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionMatrix();

private:
    
    // IInputHandler
    void OnKeyPressed(int key, int mod) override;
    void OnKeyReleased(int key, int mod) override;
    void OnMousePos(double xPos, double yPos) override;
    void OnMouseScroll(double xOffset, double yOffset) override;
    bool IsMouseButtonDown(int button) override;
    //void OnKeyRepeat(int key, int mod) override;
    void OnLeftMouseButtonDown(int mod) override;
    void OnLeftMouseButtonUp(int mod) override;
    void OnRightMouseButtonDown(int mod) override;
    void OnRightMouseButtonUp(int mod) override;
    void OnMiddleMouseButtonDown(int mod) override;
    void OnMiddleMouseButtonUp(int mod) override;
    void GetMousePos(double& xPos, double& yPos) override;

private:
    glm::vec3 m_vPosition;
    glm::vec3 m_vDirection;
    glm::vec3 m_vUp;
    float m_fFOV;
    float m_fNearPlane;
    float m_fFarPlane;
    const CViewport* m_pViewport;


    // TODO : Move to CameraMovement
    double m_dLastXPos;
    double m_dLastYPos;
    double m_dSensitivity;
    glm::vec3 m_vEulerAngles; // x:pitch, y:yaw, z:roll
};

struct SCameraDef
{
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 up;
    float fov;
    float fNearPlane;
    float fFarPlane;
};