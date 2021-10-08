#pragma once

class CModel;
class CProgram;
class CShader;
class CTexture;
class CMaterial;
class CMesh;
class CModel;
class CCamera;
struct SMaterialProperties;
struct SMaterialRenderStates;
struct SMeshData;


template<typename T>
class CAssetCollection
{
public:
	const T* Get(std::string strName) const
	{
		Iter itr = m_mapAssets.find(strName);
		return itr != m_mapAssets.end() ? itr->second : nullptr;
	}

	void Add(std::string strName, T* pT)
	{
		m_mapAssets[strName] = pT;
	}

private:
	typedef std::map<std::string, T*>::const_iterator Iter;
	std::map<std::string, T*> m_mapAssets;
};


class CAssetManager
{
public:
	static bool Init();
	static CAssetManager& Get();
	static void Destroy();

	const CShader* GetShader(std::string strShaderName) const;
	const CProgram* GetProgram(std::string strProgramName) const;
	const CTexture* GetTexture(std::string strTextureName) const;
	const CMaterial* GetMaterial(std::string strMaterialName) const;
	const CModel* GetModel(std::string strModelName) const;

	const SMaterialProperties* GetMaterialProperties(std::string strName);
	const SMaterialRenderStates* GetMaterialStates(std::string strName);

private:
	CAssetManager();
	bool InitPrivate();

	void LoadShaders();
	void LoadTextures();
	void LoadMaterials();
	void LoadModels();

	CShader* LoadShader(std::string strShaderFileName);
	CTexture* LoadTexture(std::string strTextureFileName);
	CProgram* LoadProgram(std::string strProgramName);
	CModel * LoadModel(std::string strModelFileName);

	void ProcessNode(aiNode* pNode, const aiScene* pScene, std::list<SMeshData*> & listMeshData);
	SMeshData* ProcessMesh(aiMesh* pMesh, const aiScene* pScene);
	void ProcessMaterial(aiMaterial* pMaterial, std::string strModelPath);

	std::string LoadShaderFile(std::string shaderFile);
	unsigned int LoadTextureFile(std::string strTextureFile);
	unsigned char* GetTextureData(std::string strTextureFile, int& width, int& height, int& format);

private:
	static CAssetManager* s_pAssetManager;

	typedef std::map<std::string, CModel*>::const_iterator ModelIter;
	std::map<std::string, CModel*> m_mapModels;
	
	CAssetCollection<CShader> m_shaders;
	CAssetCollection<CProgram> m_programs;
	CAssetCollection<CTexture> m_textures;
	CAssetCollection<CMaterial> m_materials;
	CAssetCollection<CModel> m_models;

	CAssetCollection<SMaterialProperties> m_materialProperties;
	CAssetCollection<SMaterialRenderStates> m_materialStates;
};