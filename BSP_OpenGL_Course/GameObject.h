#pragma once

class CTransform;
class CMesh;
class CMeshRenderer;
class CMaterial;
class CCamera;
class CLight;
class CModel;

class CGameObject
{
public:
	CGameObject(CTransform * pTranform, CModel* pModel, CMesh * pMesh, CMeshRenderer * pMeshRenderer, const CMaterial * pMaterial);

	void Update();
	void Render(CCamera* pCamera, 
		std::list<CLight*>* pDirectionalLights, 
		std::list<CLight*>* pPointLights,
		std::list<CLight*>* pSpotLights);
private:
	CTransform* m_pTransform;
	CMesh* m_pMesh;
	CMeshRenderer* m_pMeshRenderer;
	const CMaterial* m_pMaterial;
	CModel* m_pModel;
};