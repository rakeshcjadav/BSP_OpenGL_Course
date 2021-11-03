#include"pch.h"
#include"AssetManager.h"
#include"Shader.h"
#include"Program.h"
#include"Texture.h"
#include"Material.h"
#include"MaterialPass.h"
#include"Mesh.h"
#include"Model.h"
#include"STB.h"


CAssetManager * CAssetManager::s_pAssetManager = nullptr;

bool CAssetManager::Init()
{
	CAssetManager* pAssetManager = new CAssetManager();
	s_pAssetManager = pAssetManager;
	if (!pAssetManager->InitPrivate())
	{
		delete pAssetManager;
		pAssetManager = nullptr;
	}
	return !!s_pAssetManager;
}

CAssetManager& CAssetManager::Get()
{
	return *s_pAssetManager;
}

void CAssetManager::Destroy()
{
	delete s_pAssetManager;
	s_pAssetManager = nullptr;
}

const CShader* CAssetManager::GetShader(std::string strShaderName) const
{
	return m_shaders.Get(strShaderName);
}

const CProgram* CAssetManager::GetProgram(std::string strProgramName) const
{
	return m_programs.Get(strProgramName);
}

const CTexture* CAssetManager::GetTexture(std::string strTextureName) const
{
	return m_textures.Get(strTextureName);
}

const CMaterial* CAssetManager::GetMaterial(std::string strMaterialName) const
{
	return m_materials.Get(strMaterialName);
}

const CModel* CAssetManager::GetModel(std::string strModelName) const
{
	return m_models.Get(strModelName);
}

const SMaterialPassProperties* CAssetManager::GetMaterialProperties(std::string strName)
{
	return m_materialProperties.Get(strName);
}

const SMaterialPassRenderStates* CAssetManager::GetMaterialStates(std::string strName)
{
	return m_materialStates.Get(strName);
}

CAssetManager::CAssetManager()
{

}

bool CAssetManager::InitPrivate()
{
	LoadShaders();
	LoadTextures();
	LoadMaterials();
	//LoadModels();
	return true;
}

void CAssetManager::LoadShaders()
{
	std::vector<std::string> shaders = {
		"unlit_vertex_shader.vert",
		"lit_vertex_shader.vert",
		"lit_vertex_normal_shader.vert",

		"unlit_fragment_shader.frag",
		"lit_fragment_shader.frag",
		"lit_fragment_diffuse_specular_shader.frag",
		"lit_fragment_diffuse_specular_normal_shader.frag",
		"lit_fragment_diffuse_normal_depth_shader.frag",

		"shadowcaster.vert",
		"shadowcaster.frag"
	};
	for (std::string shader : shaders)
	{
		m_shaders.Add(shader, LoadShader(shader));
	}

	m_programs.Add("unlit_program", new CProgram("unlit_vertex_shader.vert", "unlit_fragment_shader.frag"));
	m_programs.Add("lit_program", new CProgram("lit_vertex_shader.vert", "lit_fragment_shader.frag"));
	m_programs.Add("lit_program_dif_spec", new CProgram("lit_vertex_shader.vert", "lit_fragment_diffuse_specular_shader.frag"));
	m_programs.Add("lit_program_dif_spec_normal", new CProgram("lit_vertex_shader.vert", "lit_fragment_diffuse_specular_normal_shader.frag"));
	m_programs.Add("lit_program_dif_normal_depth", new CProgram("lit_vertex_normal_shader.vert", "lit_fragment_diffuse_normal_depth_shader.frag"));

	m_programs.Add("shadowcaster", new CProgram("shadowcaster.vert", "shadowcaster.frag"));
}

void CAssetManager::LoadTextures()
{
	std::vector<std::string> textures = {
		"minion-transparent-background-9.png",
		"minion.jpg",
		"seamless_tileable_texture.jpg",
		"container/container.png",
		"container/container_specular.png",
		"bricks2/bricks2.jpg",
		"bricks2/bricks2_normal.jpg",
		"bricks2/bricks2_disp.jpg",
		"brickwall.jpg",
		"brickwall_normal.jpg",
		"Stylized_Dry_Mud_001_basecolor.jpg",
		"Stylized_Dry_Mud_001_normal.jpg",
		"Stylized_Dry_Mud_001_roughness.jpg",
		"Substance_graph/Substance_graph_BaseColor.jpg",
		"Substance_graph/Substance_graph_Normal.jpg",
		"Substance_graph/Substance_graph_Roughness.jpg",
		"Substance_graph/Substance_graph_Height.png",
		"Substance_graph/Substance_graph_AmbientOcclusion.jpg"
	};
	for (std::string texture : textures)
	{
		m_textures.Add(texture, LoadTexture(GetTexturesPath() + texture));
	}

	m_textures.Add("shadow", new CTexture(LoadDepthTexture(glm::uvec2(1024, 1024))));
}

void CAssetManager::LoadMaterials()
{
	m_materialProperties.Add("orange", new SMaterialPassProperties(
		glm::vec3(1.0f, 0.5f, 0.31f),
		glm::vec3(1.0f, 0.5f, 0.31f),
		glm::vec3(1.0f, 0.5f, 0.31f), 1.0f, 0.0f));

	m_materialProperties.Add("green", new SMaterialPassProperties(
		glm::vec3(0.5f, 1.0f, 0.31f),
		glm::vec3(0.5f, 1.0f, 0.31f),
		glm::vec3(0.5f, 1.0f, 0.31f), 32, 1.0f));

	m_materialProperties.Add("red", new SMaterialPassProperties(
		glm::vec3(1.0f, 0.20f, 0.31f),
		glm::vec3(1.0f, 0.20f, 0.31f),
		glm::vec3(1.0f, 0.20f, 0.31f), 5, 1.0f));

	m_materialProperties.Add("white", new SMaterialPassProperties(
		glm::vec3(1.0f),
		glm::vec3(1.0f),
		glm::vec3(1.0f), 8.0f, 0.1f));

	m_materialProperties.Add("white_shiny", new SMaterialPassProperties(
		glm::vec3(1.0f),
		glm::vec3(1.0f),
		glm::vec3(1.0f), 225.0f, 0.20f));

	m_materialStates.Add("default", new SMaterialPassRenderStates(
		SMaterialPassRenderStates::BLEND_TYPE::TRANSPARENT,
		true, true,
		SMaterialPassRenderStates::FACE::BACK));

	m_materialStates.Add("shadow", new SMaterialPassRenderStates(
		SMaterialPassRenderStates::BLEND_TYPE::OPAQUE,
		true, false,
		SMaterialPassRenderStates::FACE::BACK));

	std::map<std::string, const CTexture*> mapTextures;
	mapTextures["MainTex"] = GetTexture("minion-transparent-background-9.png");
	mapTextures["SecondTex"] = GetTexture("minion.jpg");
	mapTextures["ShadowTex"] = GetTexture("shadow");

	std::map<std::string, const CTexture*> mapDiffuseSpecularTextures;
	mapDiffuseSpecularTextures["DiffuseTex"] = GetTexture("container/container.png");
	mapDiffuseSpecularTextures["SpecularTex"] = GetTexture("container/container_specular.png");
	mapDiffuseSpecularTextures["ShadowTex"] = GetTexture("shadow");

	std::map<std::string, const CTexture*> mapDiffuseNormalTextures;
	mapDiffuseNormalTextures["DiffuseTex"] = GetTexture("brickwall.jpg");
	mapDiffuseNormalTextures["SpecularTex"] = GetTexture("brickwall.jpg");
	mapDiffuseNormalTextures["NormalTex"] = GetTexture("brickwall_normal.jpg");
	mapDiffuseNormalTextures["ShadowTex"] = GetTexture("shadow");

	std::map<std::string, const CTexture*> mapGroundTexture;
	mapGroundTexture["DiffuseTex"] = GetTexture("seamless_tileable_texture.jpg");
	mapGroundTexture["SpecularTex"] = GetTexture("seamless_tileable_texture.jpg");
	mapGroundTexture["ShadowTex"] = GetTexture("shadow");

	std::map<std::string, const CTexture*> mapDryMudGroundTexture;
	mapDryMudGroundTexture["DiffuseTex"] = GetTexture("Stylized_Dry_Mud_001_basecolor.jpg");
	mapDryMudGroundTexture["SpecularTex"] = GetTexture("Stylized_Dry_Mud_001_roughness.jpg");
	mapDryMudGroundTexture["NormalTex"] = GetTexture("Stylized_Dry_Mud_001_normal.jpg");
	mapDryMudGroundTexture["ShadowTex"] = GetTexture("shadow");

	std::map<std::string, const CTexture*> mapWallTexture;
	mapWallTexture["DiffuseTex"] = GetTexture("bricks2/bricks2.jpg");
	mapWallTexture["NormalTex"] = GetTexture("bricks2/bricks2_normal.jpg");
	mapWallTexture["DepthTex"] = GetTexture("bricks2/bricks2_disp.jpg");
	mapWallTexture["ShadowTex"] = GetTexture("shadow");

	std::map < std::string, const CTexture*> mapSubstanceGraph;
	mapSubstanceGraph["DiffuseTex"] = GetTexture("Substance_graph/Substance_graph_BaseColor.jpg");
	mapSubstanceGraph["NormalTex"] = GetTexture("Substance_graph/Substance_graph_Normal.jpg");
	mapSubstanceGraph["SpecularTex"] = GetTexture("Substance_graph/Substance_graph_Roughness.jpg");
	mapSubstanceGraph["DepthTex"] = GetTexture("Substance_graph/Substance_graph_Height.png");
	mapSubstanceGraph["AmbientOcclusionTex"] = GetTexture("Substance_graph/Substance_graph_AmbientOcclusion.jpg");

	const CProgram* pProgramUnlit = GetProgram("unlit_program");
	const CProgram* pProgramLit = GetProgram("lit_program");
	const CProgram* pProgramDiffuseSpecular = GetProgram("lit_program_dif_spec");
	const CProgram* pProgramDiffuseSpecularNormal = GetProgram("lit_program_dif_spec_normal");
	const CProgram* pProgramDiffuseNormalDepth = GetProgram("lit_program_dif_normal_depth");
	const CProgram* pProgramShadowCaster = GetProgram("shadowcaster");

	const SMaterialPassProperties* pOrangeProperties = GetMaterialProperties("orange");
	const SMaterialPassProperties* pGreenProperties = GetMaterialProperties("green");
	const SMaterialPassProperties* pRedProperties = GetMaterialProperties("red");
	const SMaterialPassProperties* pWhiteProperties = GetMaterialProperties("white");
	const SMaterialPassProperties* pWhiteShinyProperties = GetMaterialProperties("white_shiny");

	const SMaterialPassRenderStates* pDefaultStates = CAssetManager::Get().GetMaterialStates("default");
	const SMaterialPassRenderStates* pShadowStates = CAssetManager::Get().GetMaterialStates("shadow");

	// Unlit
	m_materials.Add("unlit_orange", 
		new CMaterial("unlit_orange", {
			new CMaterialPass("shadow", pShadowStates, pWhiteProperties, pProgramShadowCaster, mapTextures),
			new CMaterialPass("unlit_green", pDefaultStates, pOrangeProperties, pProgramUnlit, mapTextures)
		}
	));
	m_materials.Add("unlit_green", 
		new CMaterial("unlit_green", {
			new CMaterialPass("shadow", pShadowStates, pWhiteProperties, pProgramShadowCaster, mapTextures),
			new CMaterialPass("unlit_green", pDefaultStates, pGreenProperties, pProgramUnlit, mapTextures)
		}
	));
	m_materials.Add("unlit_white",
		new CMaterial("unlit_white", {
			new CMaterialPass("shadow", pShadowStates, pWhiteProperties, pProgramShadowCaster, mapTextures),
			new CMaterialPass("unlit_white", pDefaultStates, pWhiteProperties, pProgramUnlit, mapTextures)
			}
	));

	// Lit
	m_materials.Add("lit_orange",
		new CMaterial("lit_orange", {
			new CMaterialPass("shadow", pShadowStates, pWhiteProperties, pProgramShadowCaster, mapWallTexture),
			new CMaterialPass("lit_orange", pDefaultStates, pWhiteProperties, pProgramDiffuseSpecular, mapWallTexture)
			}
	));
	m_materials.Add("lit_green",
		new CMaterial("lit_green", {
			new CMaterialPass("shadow", pShadowStates, pWhiteProperties, pProgramShadowCaster, mapWallTexture),
			new CMaterialPass("lit_green", pDefaultStates, pGreenProperties, pProgramLit, mapTextures)
			}
	));
	m_materials.Add("lit_red",
		new CMaterial("lit_red", {
			new CMaterialPass("shadow", pShadowStates, pWhiteProperties, pProgramShadowCaster, mapWallTexture),
			new CMaterialPass("lit_red", pDefaultStates, pRedProperties, pProgramLit, mapTextures)
			}
	));
	m_materials.Add("lit_white",
		new CMaterial("lit_white", {
			new CMaterialPass("shadow", pShadowStates, pWhiteProperties, pProgramShadowCaster, mapWallTexture),
			new CMaterialPass("lit_white", pDefaultStates, pWhiteShinyProperties, pProgramDiffuseSpecular, mapGroundTexture)
			}
	));

	// Diffuse Specular
	m_materials.Add("lit_diff_spec",
		new CMaterial("lit_diff_spec", {
			new CMaterialPass("shadow", pShadowStates, pWhiteProperties, pProgramShadowCaster, mapDiffuseSpecularTextures),
			new CMaterialPass("lit_diff_spec", pDefaultStates, pWhiteShinyProperties, pProgramDiffuseSpecular, mapDiffuseSpecularTextures)
			}
	));

	// Diffuse Specular Normal
	m_materials.Add("lit_diff_spec_normal",
		new CMaterial("lit_diff_spec_normal", {
			new CMaterialPass("shadow", pShadowStates, pWhiteProperties, pProgramShadowCaster, mapDryMudGroundTexture),
			new CMaterialPass("lit_diff_spec_normal", pDefaultStates, pWhiteShinyProperties, pProgramDiffuseSpecularNormal, mapDryMudGroundTexture)
			}
	));

	// 
	m_materials.Add("lit_diff_spec_normal_mud",
		new CMaterial("lit_diff_spec_normal_mud", {
			new CMaterialPass("shadow", pShadowStates, pWhiteProperties, pProgramShadowCaster, mapDryMudGroundTexture),
			new CMaterialPass("lit_diff_spec_normal_mud", pDefaultStates, pWhiteProperties, pProgramDiffuseSpecularNormal, mapDryMudGroundTexture)
			}
	));

	// Diffuse Normal Depth
	m_materials.Add("lit_diff_normal_depth",
		new CMaterial("lit_diff_normal_depth", {
			new CMaterialPass("shadow", pShadowStates, pWhiteProperties, pProgramShadowCaster, mapWallTexture),
			new CMaterialPass("lit_diff_normal_depth", pDefaultStates, pWhiteShinyProperties, pProgramDiffuseNormalDepth, mapWallTexture)
			}
	));

	// Diffuse Normal Depth
	m_materials.Add("substance_graph",
		new CMaterial("substance_graph", {
			new CMaterialPass("shadow", pShadowStates, pWhiteProperties, pProgramShadowCaster, mapSubstanceGraph),
			new CMaterialPass("substance_graph", pDefaultStates, pWhiteShinyProperties, pProgramDiffuseNormalDepth, mapSubstanceGraph)
			}
	));
}

void CAssetManager::LoadModels()
{
	std::vector<std::string> models = {
		"backpack/backpack.obj"
	};
	for (std::string model : models)
	{
		m_models.Add(model, LoadModel(model));
	}
}

CShader* CAssetManager::LoadShader(std::string strShaderFileName)
{
	std::string strShaderSource = LoadShaderFile(strShaderFileName);
	
	CShader* pShader = nullptr;
	if (strShaderFileName.find(".vert") != std::string::npos)
	{
		pShader = new CShader(CShader::SHADER_TYPE::VERTEX, strShaderSource);
	}
	else if (strShaderFileName.find(".frag") != std::string::npos)
	{
		pShader = new CShader(CShader::SHADER_TYPE::FRAGMENT, strShaderSource);
	}
	else
	{
		assert("Unknown Shader type!");
	}
	return pShader;
}

CTexture* CAssetManager::LoadTexture(std::string strTextureFileName)
{
	return new CTexture(LoadTextureFile(strTextureFileName));
}

std::string CAssetManager::LoadShaderFile(std::string shaderFile)
{
	// All shaders are put in specific folder
	std::string shaderFilePath = GetShaderPath();

	std::ifstream file(shaderFilePath.append(shaderFile));
	//LOG_INFO << "Loading Shader : " << shaderFile << LOG_END;
	std::string shaderSource;
	if (file.is_open())
	{
		std::string line;
		std::regex reg("[ ]*#include[ ]*\"(.*)\"");
		while (std::getline(file, line))
		{
			std::smatch matches;
			// search and include reference shader file
			if (std::regex_search(line, matches, reg))
			{
				shaderSource += LoadShaderFile(matches.str(1));
			}
			else
			{
				shaderSource += line + "\n";
			}
		}
	}

	file.close();
	return shaderSource;
}

unsigned int CAssetManager::LoadTextureFile(std::string strTextureFile)
{
	int width, height, format;
	unsigned char* data = GetTextureData(strTextureFile, width, height, format);

	unsigned int texture_id;
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data); // 24 bits 

	// Texture wrapping : Default mode : REPEAT in both directions
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glGenerateMipmap(GL_TEXTURE_2D);

	// Tri-Linear filters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	return texture_id;
}

unsigned int CAssetManager::LoadDepthTexture(glm::uvec2 size)
{
	unsigned int idDepthMap;
	glGenTextures(1, &idDepthMap);
	glBindTexture(GL_TEXTURE_2D, idDepthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, size.x, size.y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	return idDepthMap;
}

unsigned char* CAssetManager::GetTextureData(std::string strTextureFile, int& width, int& height, int& format)
{
	int nrChannels;
	std::string filePath = strTextureFile;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);

	if (data == nullptr)
	{
		LOG_ERROR << "Failed to load texture: " << filePath;
		return 0;
	}

	//LOG_INFO << "Texture loaded successfully: "<< filePath;
	//LOG_INFO << "Width: " << width << " Height: " << height << " Channels: "<< nrChannels;

	format = GL_RGB;
	if (nrChannels > 3)
	{
		format = GL_RGBA;
	}
	else if (nrChannels == 1)
	{
		format = GL_RED;
	}

	return data;
}

CProgram* CAssetManager::LoadProgram(std::string strProgramName)
{
	return nullptr;
}

CModel * CAssetManager::LoadModel(std::string strModelFileName)
{
	Assimp::Importer importer;
	std::filesystem::path filePath = std::filesystem::path(GetModelPath() + strModelFileName);
	filePath.remove_filename();
	std::string strModelPath(filePath.string());
	const aiScene* pScene = importer.ReadFile(GetModelPath() + strModelFileName, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	
	if (!pScene || pScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !pScene->mRootNode)
	{
		LOG_ERROR << "ERROR::ASSIMP::" << importer.GetErrorString() << LOG_END;
		return nullptr;
	}
	std::list<SMeshData*> listMeshData;
	CMaterial* pMaterial = nullptr;
	ProcessNode(pScene->mRootNode, pScene, listMeshData);

	for (unsigned int i = 0; i < pScene->mNumMaterials; i++)
	{
		ProcessMaterial(pScene->mMaterials[i], strModelPath);
	}
	
	aiString strMaterialName;
	pScene->mMaterials[1]->Get(AI_MATKEY_NAME, strMaterialName);
	return new CModel(listMeshData, GetMaterial(strMaterialName.C_Str()));
}

void CAssetManager::ProcessNode(aiNode* pNode, const aiScene* pScene, std::list<SMeshData*> & listMeshData)
{
	for (unsigned int i = 0; i < pNode->mNumMeshes; i++)
	{
		aiMesh* pMesh = pScene->mMeshes[pNode->mMeshes[i]];
		listMeshData.push_back(ProcessMesh(pMesh, pScene));
	}

	for (unsigned int i = 0; i < pNode->mNumChildren; i++)
	{
		ProcessNode(pNode->mChildren[i], pScene, listMeshData);
	}
}

SMeshData* CAssetManager::ProcessMesh(aiMesh* pMesh, const aiScene* pScene)
{
	SMeshData * pMeshData = new SMeshData();
	pMeshData->strName = pMesh->mName.C_Str();
	SVertex vertex;
	for (unsigned int i = 0; i < pMesh->mNumVertices; i++)
	{
		vertex.position = glm::make_vec3(&pMesh->mVertices[i].x);
		vertex.normal = glm::make_vec3(&pMesh->mNormals[i].x);
		vertex.tangent = glm::make_vec3(&pMesh->mTangents[i].x);
		vertex.bitangent = glm::make_vec3(&pMesh->mBitangents[i].x);

		if (pMesh->mTextureCoords[0])
		{
			vertex.uv = glm::make_vec2(&pMesh->mTextureCoords[0][i].x);
		}
		pMeshData->aVertices.push_back(vertex);
	}
	for (unsigned int i = 0; i < pMesh->mNumFaces; i++)
	{
		aiFace & face = pMesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			pMeshData->aIndices.push_back(face.mIndices[j]);
		}
	}
	return pMeshData;
}

void CAssetManager::ProcessMaterial(aiMaterial* pMaterial, std::string strModelPath)
{
	aiString name;
	pMaterial->Get(AI_MATKEY_NAME, name);
	aiColor3D ambientColor;
	pMaterial->Get(AI_MATKEY_COLOR_AMBIENT, ambientColor);

	aiColor3D diffuseColor;
	pMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, diffuseColor);

	aiColor3D specularColor;
	pMaterial->Get(AI_MATKEY_COLOR_SPECULAR, specularColor);

	ai_real shininess;
	pMaterial->Get(AI_MATKEY_SHININESS, shininess);

	aiBlendMode blendMode;
	pMaterial->Get(AI_MATKEY_BLEND_FUNC, blendMode);

	m_materialProperties.Add(name.C_Str(), new SMaterialPassProperties(
		glm::make_vec3(&ambientColor.r),
		glm::make_vec3(&diffuseColor.r),
		glm::make_vec3(&specularColor.r), shininess, 1.0f));

	aiString diffuseTexture;
	pMaterial->Get(AI_MATKEY_TEXTURE_DIFFUSE(0), diffuseTexture);

	aiString specularTexture;
	pMaterial->Get(AI_MATKEY_TEXTURE_SPECULAR(0), specularTexture);

	aiString normalTexture;
	pMaterial->Get(AI_MATKEY_TEXTURE_HEIGHT(0), normalTexture);

	aiString aoTexture;
	pMaterial->Get(AI_MATKEY_TEXTURE_AMBIENT(0), aoTexture);

	if(diffuseTexture.length > 0)
		m_textures.Add(diffuseTexture.C_Str(), LoadTexture(strModelPath + diffuseTexture.C_Str()));
	if (specularTexture.length > 0)
		m_textures.Add(specularTexture.C_Str(), LoadTexture(strModelPath + specularTexture.C_Str()));
	if (normalTexture.length > 0)
		m_textures.Add(normalTexture.C_Str(), LoadTexture(strModelPath + normalTexture.C_Str()));
	if (aoTexture.length > 0)
		m_textures.Add(aoTexture.C_Str(), LoadTexture(strModelPath + aoTexture.C_Str()));

	std::map<std::string, const CTexture*> mapTextures;
	mapTextures["DiffuseTex"] = CAssetManager::Get().GetTexture(diffuseTexture.C_Str());
	mapTextures["SpecularTex"] = CAssetManager::Get().GetTexture(specularTexture.C_Str());
	mapTextures["NormalTex"] = CAssetManager::Get().GetTexture(normalTexture.C_Str());
	mapTextures["AmbientOcclusionTex"] = CAssetManager::Get().GetTexture(aoTexture.C_Str());

	std::string strMaterialName = name.C_Str();
	CMaterial* pMat = new CMaterial(strMaterialName, {
		new CMaterialPass("shadow", 
			GetMaterialStates("default"), GetMaterialProperties(name.C_Str()), 
			GetProgram("shadow_caster"), mapTextures),
		new CMaterialPass(strMaterialName,
			GetMaterialStates("default"), GetMaterialProperties(name.C_Str()),
			GetProgram("lit_program_dif_spec_normal"), mapTextures) 
		}
	);
	m_materials.Add(name.C_Str(), pMat);
}