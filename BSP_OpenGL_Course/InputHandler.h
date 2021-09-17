#pragma once

class IInputDelegator;

class IInputHandler
{
public:
    IInputHandler(IInputDelegator* pDelegator);
    virtual ~IInputHandler();
    virtual void OnKeyPressed(int key, int mod) = 0;
    virtual void OnKeyReleased(int key, int mod) = 0;
    virtual void OnMousePos(double xPos, double yPos) = 0;
    virtual void OnMouseScroll(double xOffset, double yOffset) = 0;
    virtual bool IsMouseButtonDown(int button) = 0;
    virtual void OnLeftMouseButtonDown(int mod) = 0;
    virtual void OnLeftMouseButtonUp(int mod) = 0;
    virtual void OnRightMouseButtonDown(int mod) = 0;
    virtual void OnRightMouseButtonUp(int mod) = 0;
    virtual void OnMiddleMouseButtonDown(int mod) = 0;
    virtual void OnMiddleMouseButtonUp(int mod) = 0;
    virtual void GetMousePos(double& xPos, double& yPos) = 0;
    virtual bool IsKeyPressed(int key) = 0;

    virtual void Update() = 0;

protected:
    IInputDelegator* m_pDelegator;
};