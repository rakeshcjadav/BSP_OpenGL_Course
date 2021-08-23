#include"InputHandler.h"
#include"InputDelegator.h"

IInputHandler::IInputHandler(IInputDelegator* pDelegator)
{
    m_pDelegator = pDelegator;
    m_pDelegator->Attach(this);
}

IInputHandler::~IInputHandler()
{
    if (m_pDelegator)
        m_pDelegator->Detach(this);
}