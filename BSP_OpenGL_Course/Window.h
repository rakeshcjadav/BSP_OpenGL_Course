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

class CWindow : public IInputDelegator
{
public:
    static CWindow* Create(int height, int width, std::string strName);
    void CreateScene(); // TODO: Move to Scene class
    void RenderLoop();
    bool IsWindowClosed() const;
    void RenderOneFrame();
    void MakeCurrent();

    virtual ~CWindow();
private:
    CWindow();
    bool Init(int height, int width, std::string strName);
    GLFWwindow* GetGLFWWindow();
    static void KeyCallBack(GLFWwindow* pWindow, int key, int scancode, int action, int mod);

    // IInputDelegator
    virtual void NotifyKeyPressed(int key, int mod) override;
    virtual void NotifyKeyReleased(int key, int mod) override;

private:
    GLFWwindow* m_pWindow;
    CViewport* m_pViewport;
    CCamera* m_pCamera;

    // TODO: Move to scene class
    CMesh* m_pMesh;
    CProgram* m_pProgram;
    CTexture* m_pTexture1;
    CTexture* m_pTexture2;

    static std::map<GLFWwindow*, CWindow*> s_mapWindows;
};