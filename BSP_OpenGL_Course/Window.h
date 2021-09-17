#pragma once
#include<string>
#include<map>
#include"InputDelegator.h"

struct GLFWwindow;
class CViewport;
class CCamera;
class CMesh;
class CProgram;
class CTexture;
class CCameraController;
class CLight;
class CMaterial;
class CScene;

class CWindow : public IInputDelegator
{
public:
    static CWindow* Create(int height, int width, std::string strName);
    void CreateScene(); // TODO: Move to Scene class
    void RenderLoop();
    bool IsWindowClosed() const;
    void RenderOneFrame();
    void MakeCurrent();

    ~CWindow();
private:
    CWindow();
    bool Init(int width, int height, std::string strName);
    GLFWwindow* GetGLFWWindow();
    static void KeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mod);
    static void CursorPosCallback(GLFWwindow* pWindow, double xPos, double yPos);
    static void ScrollCallback(GLFWwindow* pWindow, double xOffset, double yOffset);
    static void MouseButtonCallback(GLFWwindow* pWindow, int button, int action, int mod);

    // IInputDelegator
    void NotifyKeyPressed(int key, int mod) override;
    void NotifyKeyReleased(int key, int mod) override;
    void NotifyCursorPos(double xPos, double yPos) override;
    void NotifyMouseScroll(double xOffset, double yOffset) override;
    bool IsMouseButtonDown(int button) override;
    void NotifyMouseButton(int button, int action, int mod) override;
    void GetMousePos(double& xPos, double& yPos) override;
    bool IsKeyPressed(int key) override;

private:
    GLFWwindow* m_pWindow;
    CViewport* m_pViewport;
    CViewport* m_pViewport2;
    CScene* m_pScene;

    // TODO : Move to Game object as component
    CCameraController* m_pCameraController;

    static std::map<GLFWwindow*, CWindow*> s_mapWindows;
};