#pragma once
#include<string>

// Forward Declarations

class CShader
{
public:
	enum SHADER_TYPE
	{
		VERTEX,
		FRAGMENT
	};
public:
	CShader(SHADER_TYPE type, std::string shaderFile /* vertex_shader.glsl */);
	~CShader();
	unsigned int GetID();

private:
	std::string LoadShader(std::string shaderFile);

private:
	unsigned int m_IDShader;
};