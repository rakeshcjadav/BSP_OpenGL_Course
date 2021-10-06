#include"GameObject.h"
#include"MeshRenderer.h"
#include"Transform.h"
#include"Material.h"
#include"Model.h"


CGameObject::CGameObject(CTransform* pTranform, CModel* pModel, CMesh* pMesh, CMeshRenderer* pMeshRenderer, const CMaterial* pMaterial)
{
    m_pTransform = pTranform;
    m_pMesh = pMesh;
    m_pMeshRenderer = pMeshRenderer;
    m_pMaterial = pMaterial;
    m_pModel = pModel;
}

void CGameObject::Update()
{

}

void CGameObject::Render(CCamera* pCamera,
    std::list<CLight*>* pDirectionalLights,
    std::list<CLight*>* pPointLights,
    std::list<CLight*>* pSpotLights)
{
    if(m_pMesh)
        m_pMeshRenderer->Render(m_pMesh, m_pTransform, m_pMaterial, pCamera, pDirectionalLights, pPointLights, pSpotLights);
    else if(m_pModel)
        m_pMeshRenderer->Render(m_pModel, m_pTransform, pCamera, pDirectionalLights, pPointLights, pSpotLights);
}