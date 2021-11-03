#pragma once

class CMesh;
class CMaterial;
class CCamera;
class CLight;
class CTransform;
class CModel;

class CMeshRenderer
{
public:
	CMeshRenderer();

	void Render(CMesh * pMesh, CTransform * pTransform, const CMaterialPass * pMaterial, CCamera * pCamera, 
		std::list<CLight*>* pDirectionalLights = nullptr,
		std::list<CLight*>* pPointLights = nullptr,
		std::list<CLight*>* pSpotLights = nullptr);


	void Render(const CModel* pModel, CTransform* pTransform, CCamera* pCamera,
		std::list<CLight*>* pDirectionalLights = nullptr,
		std::list<CLight*>* pPointLights = nullptr,
		std::list<CLight*>* pSpotLights = nullptr,
		bool bShadowCasterPass = false);

private:

};