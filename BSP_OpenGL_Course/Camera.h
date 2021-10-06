#pragma once

// Forward Declarations
struct SCameraDef;
class CViewport;
class CScene;

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

    void SetSize(float size);
    float GetSize() const;

    int GetWidth() const;
    int GetHeight() const;

    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionMatrix();

    void Assign(CViewport* pViewport);
    void SetScene(CScene* pScene);

    void Update();

private:
    glm::vec3 m_vPosition;
    glm::vec3 m_vDirection;
    glm::vec3 m_vUp;
    float m_fFOV;
    float m_fSize;
    float m_fNearPlane;
    float m_fFarPlane;
    const CViewport* m_pViewport;
    CScene* m_pScene;
};

struct SCameraDef
{
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 up;
    float fov;
    float fNearPlane;
    float fFarPlane;

    SCameraDef()
    {
    }
};