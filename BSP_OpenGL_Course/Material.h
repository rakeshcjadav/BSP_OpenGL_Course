#pragma once
#include<string>
#include<list>
#include"GLM.h"

// Forward Declarations
class CProgram;
class CTexture;
struct SMaterialProperties;


class CMaterial
{
public:
    enum class BlendType
    {
        TRANSPARENT = 0,
        OPAQUE = 1
    };
public:
    CMaterial(std::string strName, BlendType blendType, SMaterialProperties * pProperties, CProgram * pProgram, std::list<CTexture*> listTextures);
    void Bind();
    void SetUniform(std::string name, int value);
    void SetUniform(std::string name, float value);
    void SetUniform(std::string name, glm::vec3& value);
    void SetUniform(std::string name, glm::vec4& value);
    void SetUniform(std::string name, glm::mat4& value);
    void SetUniform(std::string name, float* value);
private:
    std::string m_strName;
    BlendType m_blendType = BlendType::OPAQUE;
    SMaterialProperties* m_pProperties;
    CProgram* m_pProgram;
    std::list<CTexture*> m_listTextures;
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