#pragma once

class IInputDelegator;

class IInputHandler
{
public:
    IInputHandler(IInputDelegator* pDelegator);
    virtual ~IInputHandler();
    virtual void OnKeyPressed(int key, int mod) = 0;
    virtual void OnKeyReleased(int key, int mod) = 0;

private:
    IInputDelegator* m_pDelegator;
};