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
    void OnKeyPressed(int key, int mod) override;
    void OnKeyReleased(int key, int mod) override;
    //void OnKeyRepeat(int key, int mod) override;
private:
    glm::vec3 m_vPosition;
    glm::vec3 m_vDirection;
    glm::vec3 m_vUp;
    float m_fFOV;
    float m_fNearPlane;
    float m_fFarPlane;
    const CViewport* m_pViewport;
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