#include"pch.h"
#include"Component.h"

template<class T>
T* CComponent<T>::GetComponent()
{
	return T;
}

template<class T>
CGameObject* CComponent<T>::GetGameObject()
{
	return m_pGameObject;
}