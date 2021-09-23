#pragma once
#include<list>
#include<map>
#include<typeinfo>

class CTransform;
class CMesh;
class CMeshRenderer;
class CMaterial;
class CCamera;
class CLight;

class CGameObject
{
public:
    CGameObject(CTransform * pTranform, CMesh * pMesh, CMeshRenderer * pMeshRenderer, CMaterial * pMaterial);

    void Update();
    void Render(CCamera* pCamera, 
        std::list<CLight*>* pDirectionalLights, 
        std::list<CLight*>* pPointLights,
        std::list<CLight*>* pSpotLights);
private:
    CTransform* m_pTransform;
    CMesh* m_pMesh;
    CMeshRenderer* m_pMeshRenderer;
    CMaterial* m_pMaterial;
};