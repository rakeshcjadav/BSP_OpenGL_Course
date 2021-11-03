#pragma once

// Forward Declarations
class CMaterialPass;

class CMaterial
{
public:
	
public:
	CMaterial(std::string strName, std::vector<const CMaterialPass*> listPasses);
	const CMaterialPass* GetPass(unsigned int passIndex) const;
	void Bind(unsigned int passIndex);
	void SetUniform(std::string name, int value) const;
	void SetUniform(std::string name, float value) const;
	void SetUniform(std::string name, glm::vec3& value) const;
	void SetUniform(std::string name, glm::vec4& value) const;
	void SetUniform(std::string name, glm::mat4& value) const;
	void SetUniform(std::string name, float* value) const;
private:
	std::string m_strName;
	std::vector<const CMaterialPass*> m_listPasses;
	unsigned int m_iActivePass;
};