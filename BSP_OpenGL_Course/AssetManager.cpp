#include"pch.h"
#include"AssetManager.h"
#include"Shader.h"
#include"Program.h"
#include"Texture.h"
#include"Material.h"
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

const SMaterialProperties* CAssetManager::GetMaterialProperties(std::string strName)
{
	return m_materialProperties.Get(strName);
}

const SMaterialRenderStates* CAssetManager::GetMaterialStates(std::string strName)
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
	return true;
}

void CAssetManager::LoadShaders()
{
	std::vector shaders{
		"unlit_vertex_shader.vert",
		"lit_vertex_shader.vert",

		"unlit_fragment_shader.frag",
		"lit_fragment_shader.frag",
		"lit_fragment_diffuse_specular_shader.frag"
	};
	for (std::string shader : shaders)
	{
		m_shaders.Add(shader, LoadShader(shader));
	}

	m_programs.Add("unlit_program", new CProgram("unlit_vertex_shader.vert", "unlit_fragment_shader.frag"));
	m_programs.Add("lit_program", new CProgram("lit_vertex_shader.vert", "lit_fragment_shader.frag"));
	m_programs.Add("lit_program_dif_spec", new CProgram("lit_vertex_shader.vert", "lit_fragment_diffuse_specular_shader.frag"));

}

void CAssetManager::LoadTextures()
{
	std::vector textures{
		"minion-transparent-background-9.png",
		"minion.jpg",
		"seamless_tileable_texture.jpg",
		"container\\container.png",
		"container\\container_specular.png",
		"backpack\\diffuse.jpg",
		"backpack\\specular.jpg",
		"bricks2.jpg"
	};
	for (std::string texture : textures)
	{
		m_textures.Add(texture, LoadTexture(texture));
	}
}

void CAssetManager::LoadMaterials()
{
	m_materialProperties.Add("orange", new SMaterialProperties(
		glm::vec3(1.0f, 0.5f, 0.31f),
		glm::vec3(1.0f, 0.5f, 0.31f),
		glm::vec3(1.0f, 0.5f, 0.31f), 1.0f, 0.0f));

	m_materialProperties.Add("green", new SMaterialProperties(
		glm::vec3(0.5f, 1.0f, 0.31f),
		glm::vec3(0.5f, 1.0f, 0.31f),
		glm::vec3(0.5f, 1.0f, 0.31f), 32, 1.0f));

	m_materialProperties.Add("red", new SMaterialProperties(
		glm::vec3(1.0f, 0.20f, 0.31f),
		glm::vec3(1.0f, 0.20f, 0.31f),
		glm::vec3(1.0f, 0.20f, 0.31f), 5, 1.0f));

	m_materialProperties.Add("white", new SMaterialProperties(
		glm::vec3(1.0f),
		glm::vec3(1.0f),
		glm::vec3(1.0f), 0.0f, 0.1f));

	m_materialProperties.Add("white_shiny", new SMaterialProperties(
		glm::vec3(1.0f),
		glm::vec3(1.0f),
		glm::vec3(1.0f), 225.0f, 1.0f));

	m_materialStates.Add("default", new SMaterialRenderStates(
		SMaterialRenderStates::BLEND_TYPE::TRANSPARENT,
		true, true,
		SMaterialRenderStates::FACE::BACK));

	std::map<std::string, const CTexture*> mapTextures;
	mapTextures["MainTex"] = GetTexture("minion-transparent-background-9.png");
	mapTextures["SecondTex"] = GetTexture("minion.jpg");

	std::map<std::string, const CTexture*> mapDiffuseSpecularTextures;
	mapDiffuseSpecularTextures["DiffuseTex"] = GetTexture("container\\container.png");
	mapDiffuseSpecularTextures["SpecularTex"] = GetTexture("container\\container_specular.png");

	std::map<std::string, const CTexture*> mapGroundTexture;
	mapGroundTexture["DiffuseTex"] = GetTexture("seamless_tileable_texture.jpg");
	mapGroundTexture["SpecularTex"] = GetTexture("seamless_tileable_texture.jpg");

	std::map<std::string, const CTexture*> mapWallTexture;
	mapWallTexture["DiffuseTex"] = GetTexture("bricks2.jpg");
	mapWallTexture["SpecularTex"] = GetTexture("bricks2.jpg");

	const CProgram* pProgramUnlit = GetProgram("unlit_program");
	const CProgram* pProgramLit = GetProgram("lit_program");
	const CProgram* pProgramDiffuseSpecular = GetProgram("lit_program_dif_spec");

	const SMaterialProperties* pOrangeProperties = GetMaterialProperties("orange");
	const SMaterialProperties* pGreenProperties = GetMaterialProperties("green");
	const SMaterialProperties* pRedProperties = GetMaterialProperties("red");
	const SMaterialProperties* pWhiteProperties = GetMaterialProperties("white");
	const SMaterialProperties* pWhiteShinyProperties = GetMaterialProperties("white_shiny");

	const SMaterialRenderStates* pDefaultStates = CAssetManager::Get().GetMaterialStates("default");

	// Unlit
	m_materials.Add("unlit_orange", new CMaterial("unlit_orange", pDefaultStates, pOrangeProperties, pProgramUnlit, mapTextures));
	m_materials.Add("unlit_green", new CMaterial("unlit_green", pDefaultStates, pGreenProperties, pProgramUnlit, mapTextures));
	m_materials.Add("unlit_white", new CMaterial("unlit_white", pDefaultStates, pWhiteProperties, pProgramUnlit, mapTextures));

	// Lit
	m_materials.Add("lit_orange",  new CMaterial("lit_orange", pDefaultStates, pWhiteProperties, pProgramDiffuseSpecular, mapWallTexture));
	m_materials.Add("lit_green",  new CMaterial("lit_green", pDefaultStates, pGreenProperties, pProgramLit, mapTextures));
	m_materials.Add("lit_red", new CMaterial("lit_red", pDefaultStates, pRedProperties, pProgramLit, mapTextures));
	m_materials.Add("lit_white", new CMaterial("lit_white", pDefaultStates, pWhiteShinyProperties, pProgramDiffuseSpecular, mapGroundTexture));

	// Diffuse Specular
	m_materials.Add("lit_diff_spec", new CMaterial("lit_diff_spec", pDefaultStates, pWhiteShinyProperties, pProgramDiffuseSpecular, mapDiffuseSpecularTextures));
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

unsigned char* CAssetManager::GetTextureData(std::string strTextureFile, int& width, int& height, int& format)
{
	int nrChannels;
	std::string filePath = GetTexturesPath() + strTextureFile;
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
		format = GL_RGBA;

	return data;
}

CProgram* CAssetManager::LoadProgram(std::string strProgramName)
{
	return nullptr;
}