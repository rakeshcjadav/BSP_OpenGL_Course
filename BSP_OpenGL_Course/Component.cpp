#include"pch.h"
#include"Component.h"

template<class T>
T* CComponent<T>::GetComponent()
{
	T *a = nullptr;
	return a;
}

template<class T>
CGameObject* CComponent<T>::GetGameObject()
{
	return m_pGameObject;
}