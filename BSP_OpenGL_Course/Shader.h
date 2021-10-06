#pragma once
#include<string>

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

private:
	unsigned int m_IDShader;
};