#pragma once
#include<list>

class IInputHandler;

class IInputDelegator
{
public:
    void Attach(IInputHandler* pHandler);
    void Detach(IInputHandler* pHandler);

    virtual void NotifyKeyPressed(int key, int mod) = 0;
    virtual void NotifyKeyReleased(int key, int mod)  = 0;
    virtual void NotifyCursorPos(double xPos, double yPos) = 0;
    virtual void NotifyMouseScroll(double xOffset, double yOffset) = 0;
    virtual bool IsMouseButtonDown(int button) = 0;
    virtual void NotifyMouseButton(int button, int action, int mod) = 0;
    virtual void GetMousePos(double& xPos, double& yPos) = 0;
protected:
    std::list<IInputHandler*> m_listHandler;
};