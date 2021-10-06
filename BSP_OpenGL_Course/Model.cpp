#include"pch.h"
#include"Model.h"
#include"Mesh.h"
#include"Texture.h"
#include"Program.h"
#include"Material.h"


CModel* CModel::LoadModel(std::string strFileName)
{
    CModel* pModel = new CModel();
    pModel->LoadPrivate(strFileName);
    return pModel;
}

CModel::CModel()
{

}

CMaterial* CModel::GetMaterial()
{
    return m_pMaterial;
}

void CModel::Render()
{
    for (CMesh* pMesh : m_listMeshes)
    {
        pMesh->Bind();
        pMesh->Render();
        pMesh->UnBind();
    }
}

bool CModel::LoadPrivate(std::string strFileName)
{
    Assimp::Importer importer;
    const aiScene * pScene = importer.ReadFile(GetModelPath() + strFileName, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!pScene || pScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !pScene->mRootNode)
    {
        LOG_ERROR << "ERROR::ASSIMP::" << importer.GetErrorString() << LOG_END;
        return false;
    }
    ProcessNode(pScene->mRootNode, pScene);
    return true;
}

void CModel::ProcessNode(aiNode * pNode, const aiScene * pScene)
{
    for (unsigned int i = 0; i < pNode->mNumMeshes; i++)
    {
        aiMesh * pMesh = pScene->mMeshes[pNode->mMeshes[i]];
        m_listMeshes.push_back(ProcessMesh(pMesh, pScene));
    }

    for (unsigned int i = 0; i < pNode->mNumChildren; i++)
    {
        ProcessNode(pNode->mChildren[i], pScene);
    }
}

CMesh* CModel::ProcessMesh(aiMesh* pMesh, const aiScene* pScene)
{
    SMeshData meshData;
    meshData.strName = pMesh->mName.C_Str();
    SVertex vertex;
    for (unsigned int i = 0; i < pMesh->mNumVertices; i++)
    {
        vertex.position = glm::make_vec3(&pMesh->mVertices[i].x);
        vertex.normal = glm::make_vec3(&pMesh->mNormals[i].x);
        
        if (pMesh->mTextureCoords[0])
        {
            vertex.uv = glm::make_vec2(&pMesh->mTextureCoords[0][i].x);
        }
        meshData.aVertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < pMesh->mNumFaces; i++)
    {
        aiFace face = pMesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            meshData.aIndices.push_back(face.mIndices[j]);
        }
    }

    if (pMesh->mMaterialIndex >= 0)
    {
        aiMaterial* pMaterial = pScene->mMaterials[pMesh->mMaterialIndex];

        aiString name;
        pMaterial->Get(AI_MATKEY_NAME, name);
        aiColor3D ambientColor;
        pMaterial->Get(AI_MATKEY_COLOR_AMBIENT, ambientColor);

        aiColor3D diffuseColor;
        pMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, diffuseColor);

        aiColor3D specularColor;
        pMaterial->Get(AI_MATKEY_COLOR_SPECULAR, specularColor);

        aiString diffuseTexture;
        pMaterial->Get(AI_MATKEY_TEXTURE_DIFFUSE(0), diffuseTexture);

        aiString specularTexture;
        pMaterial->Get(AI_MATKEY_TEXTURE_SPECULAR(0), specularTexture);

        ai_real shininess;
        pMaterial->Get(AI_MATKEY_SHININESS, shininess);

        aiBlendMode blendMode;
        pMaterial->Get(AI_MATKEY_BLEND_FUNC, blendMode);

        for (unsigned int i = 0; i < pMaterial->mNumProperties; i++)
        {
            

            //pMaterial->
           // LOG_INFO << pMaterial->mProperties[i]->mKey.C_Str() << " " <<  pMaterial->mProperties[i]->mSemantic << pMaterial->mProperties[i]->mType << LOG_END;
        }
    }
    if (m_pMaterial == nullptr)
    {
        std::map<std::string, const CTexture*> mapDiffuseSpecularTextures;
        mapDiffuseSpecularTextures["DiffuseTex"] = CAssetManager::Get().GetTexture("backpack\\diffuse.jpg");
        mapDiffuseSpecularTextures["SpecularTex"] = CAssetManager::Get().GetTexture("backpack\\specular.jpg");

        const CProgram* pProgramDiffuseSpecular = CAssetManager::Get().GetProgram("lit_program_dif_spec");
        const SMaterialProperties* pWhiteProperties = CAssetManager::Get().GetMaterialProperties("white_shiny");
        const SMaterialRenderStates* pDefaultStates = CAssetManager::Get().GetMaterialStates("default");

        m_pMaterial = new CMaterial("lit_diff_spec", pDefaultStates, pWhiteProperties, pProgramDiffuseSpecular, mapDiffuseSpecularTextures);
    }
    return new CMesh(&meshData);
}