#pragma once
#include<list>

class CMesh;
class CMaterial;
class CCamera;
class CLight;
class CTransform;

class CMeshRenderer
{
public:
    CMeshRenderer();

    void Render(CMesh * pMesh, CTransform * pTransform, CMaterial * pMaterial, CCamera * pCamera, std::list<CLight*> * pListLights);

private:

};