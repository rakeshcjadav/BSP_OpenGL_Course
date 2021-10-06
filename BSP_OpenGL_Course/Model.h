#pragma once

class CMesh;
class CMaterial;

class CModel
{
public:
    static CModel* LoadModel(std::string strFileName);
    CModel();
    CMaterial* GetMaterial();
    void Render();
private:
    bool LoadPrivate(std::string strFileName);
    void ProcessNode(aiNode* pNode, const aiScene* pScene);
    CMesh* ProcessMesh(aiMesh* pMesh, const aiScene* pScene);
private:
    std::list<CMesh*> m_listMeshes;
    CMaterial* m_pMaterial;
};