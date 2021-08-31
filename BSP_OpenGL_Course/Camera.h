#pragma once
#include "GLM.h"
#include "InputHandler.h"

// Forward Declarations
struct SCameraDef;
class CViewport;

class CCamera
{
public:
    CCamera(const SCameraDef * pCameraDef, const CViewport * pViewport);
    
    void SetPosition(glm::vec3 vPos);
    glm::vec3 GetPosition() const;
    
    void SetDirection(glm::vec3 vDirection);
    glm::vec3 GetDirection() const;
    
    void SetUp(glm::vec3 vUp);
    glm::vec3 GetUp() const;

    void SetFOV(float fov);
    float GetFOV() const;

    int GetWidth() const;
    int GetHeight() const;
    
    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionMatrix();

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