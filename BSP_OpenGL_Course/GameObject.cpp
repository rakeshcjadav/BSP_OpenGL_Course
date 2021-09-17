#include"GameObject.h"
#include"MeshRenderer.h"
#include"Transform.h"
#include"Material.h"

CGameObject::CGameObject(CTransform* pTranform, CMesh* pMesh, CMeshRenderer* pMeshRenderer, CMaterial* pMaterial)
{
    m_pTransform = pTranform;
    m_pMesh = pMesh;
    m_pMeshRenderer = pMeshRenderer;
    m_pMaterial = pMaterial;
}

void CGameObject::Update()
{

}

void CGameObject::Render(CCamera* pCamera, std::list<CLight*> listLights)
{
    m_pMeshRenderer->Render(m_pMesh, m_pTransform, m_pMaterial, pCamera, listLights);
}