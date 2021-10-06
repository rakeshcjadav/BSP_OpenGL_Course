#include"pch.h"
#include"InputDelegator.h"

void IInputDelegator::Attach(IInputHandler* pHandler)
{
	m_listHandler.push_back(pHandler);
}

void IInputDelegator::Detach(IInputHandler* pHandler)
{
	m_listHandler.remove(pHandler);
}