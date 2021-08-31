#pragma once
#include"InputHandler.h"
#include"GLM.h"

class CCamera;

class CCameraController : public IInputHandler
{
public:
    CCameraController(IInputDelegator* pDelegator, CCamera* pCamera);

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
    CCamera* m_pCamera;

    // TODO : Move to CameraMovement
    double m_dLastXPos;
    double m_dLastYPos;
    double m_dSensitivity;
    glm::vec3 m_vEulerAngles; // x:pitch, y:yaw, z:roll
};