#pragma once

class CGameObject;

template<typename T>
class CComponent
{
public:
    virtual void Initialize() = 0;
    virtual void Update() = 0;

    T* GetComponent();
    CGameObject* GetGameObject();

protected:
    CGameObject* m_pGameObject;
};
