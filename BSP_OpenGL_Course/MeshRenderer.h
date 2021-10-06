#pragma once
#include<list>
#include<map>
#include<typeinfo>

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

    void Render(CMesh * pMesh, CTransform * pTransform, const CMaterial * pMaterial, CCamera * pCamera, 
        std::list<CLight*>* pDirectionalLights,
        std::list<CLight*>* pPointLights,
        std::list<CLight*>* pSpotLights);


    void Render(CModel* pModel, CTransform* pTransform, CCamera* pCamera,
        std::list<CLight*>* pDirectionalLights,
        std::list<CLight*>* pPointLights,
        std::list<CLight*>* pSpotLights);

private:

};