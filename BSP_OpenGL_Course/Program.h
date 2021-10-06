#pragma once

// Forward declarations
class CShader;

class CProgram
{
public:
	CProgram(std::string strVertexShaderFile, std::string strFragmentShaderFile);

	void Use() const;
	void SetUniform(std::string name, int value) const;
	void SetUniform(std::string name, float value) const;
	void SetUniform(std::string name, const glm::vec3 & value) const;
	void SetUniform(std::string name, const glm::vec4 & value) const;
	void SetUniform(std::string name, const glm::mat4 & value) const;
	void SetUniform(std::string name, float * value) const;
private:
	void AttachShader(const CShader* pShader);
	void LinkProgram();
private:
	unsigned int m_IDProgram;
};