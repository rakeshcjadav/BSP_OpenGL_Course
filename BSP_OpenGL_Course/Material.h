#pragma once

// Forward Declarations
class CTexture;
struct SMaterialProperties;
struct SMaterialRenderStates;

class CMaterial
{
public:
	
public:
	CMaterial(std::string strName, const SMaterialRenderStates* pStates, 
		const SMaterialProperties * pProperties, 
		const CProgram * pProgram, std::map<std::string, const CTexture*> mapTextures);
	void Bind() const;
	void SetUniform(std::string name, int value) const;
	void SetUniform(std::string name, float value) const;
	void SetUniform(std::string name, glm::vec3& value) const;
	void SetUniform(std::string name, glm::vec4& value) const;
	void SetUniform(std::string name, glm::mat4& value) const;
	void SetUniform(std::string name, float* value) const;
private:
	void SetMaterialStates() const;
	void SetMaterialProperties() const;
private:
	std::string m_strName;
	const SMaterialRenderStates* m_pStates;
	const SMaterialProperties* m_pProperties;
	const CProgram* m_pProgram;
	std::map<std::string, const CTexture*> m_mapTextures;
};

struct SMaterialProperties
{
	glm::vec3 colorAmbient;
	glm::vec3 colorDiffuse;
	glm::vec3 colorSpecular;
	float fSpecularStrength;
	float fShininess;

	SMaterialProperties(glm::vec3 clrAmbient, glm::vec3 clrDiffuse, glm::vec3 clrSpecular, float fStrength, float fShine)
	{
		colorAmbient = clrAmbient;
		colorDiffuse = clrDiffuse;
		colorSpecular = clrSpecular;
		fSpecularStrength = fStrength;
		fShininess = fShine;
	}
};

struct SMaterialRenderStates
{
	enum class BLEND_TYPE
	{
		TRANSPARENT = 0,
		OPAQUE = 1
	};

	enum class FACE
	{
		BOTH = GL_FRONT_AND_BACK,
		FRONT = GL_FRONT,
		BACK = GL_BACK
	};

	BLEND_TYPE BlendType = BLEND_TYPE::TRANSPARENT;
	bool DepthTest = true;
	bool CullFace = true;
	FACE Face = FACE::BACK;

	SMaterialRenderStates(BLEND_TYPE blendType, bool depthTest, bool cullFace, FACE face)
	{
		BlendType = blendType;
		DepthTest = depthTest;
		CullFace = cullFace;
		Face = face;
	}
};