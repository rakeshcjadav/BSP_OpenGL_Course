#pragma once

// Forward Declarations

class CShader
{
public:
	enum class SHADER_TYPE
	{
		VERTEX,
		FRAGMENT
	};
public:
	CShader(SHADER_TYPE type, std::string shaderSource);
	~CShader();
	unsigned int GetID() const;
	void Print() const;

private:
	unsigned int m_IDShader;
	std::string mutable m_strSource;
};