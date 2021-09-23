#pragma once
#include<list>
#include<map>
#include<typeinfo>

class CMesh;
class CMaterial;
class CCamera;
class CLight;
class CTransform;

class CMeshRenderer
{
public:
    CMeshRenderer();

    void Render(CMesh * pMesh, CTransform * pTransform, CMaterial * pMaterial, CCamera * pCamera, 
        std::list<CLight*>* pDirectionalLights,
        std::list<CLight*>* pPointLights,
        std::list<CLight*>* pSpotLights);

private:

};