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
protected:
    std::list<IInputHandler*> m_listHandler;
};