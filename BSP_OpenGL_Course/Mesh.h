#pragma once

// Forward declarations
struct SVertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 tangent;
	glm::vec3 bitangent;
	glm::vec2 uv;

	SVertex()
	{
		position = glm::zero<glm::vec3>();
		normal = glm::zero<glm::vec3>();
		tangent = glm::zero<glm::vec3>();
		bitangent = glm::zero<glm::vec3>();
		uv = glm::zero<glm::vec2>();
	}

	SVertex(glm::vec3 _pos, glm::vec3 _normal, glm::vec2 _uv)
	{
		position = _pos;
		normal = _normal;
		tangent = glm::zero<glm::vec3>();
		bitangent = glm::zero<glm::vec3>();
		uv = _uv;
	}

	SVertex(glm::vec3 _pos, glm::vec3 _normal, glm::vec3 _tangent, glm::vec3 _bitangent, glm::vec2 _uv)
	{
		position = _pos;
		normal = _normal;
		tangent = _tangent;
		bitangent = _bitangent;
		uv = _uv;
	}
};
struct SMeshData
{
	enum class MESHTYPE
	{
		TRIANGLES = GL_TRIANGLES,
		TRIANGLE_FAN = GL_TRIANGLE_FAN,
		TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
		LINES = GL_LINES,
		LINE_STRIP = GL_LINE_STRIP,
		LINE_LOOP = GL_LINE_LOOP
	};
	std::string strName;
	std::vector<SVertex> aVertices;
	std::vector<unsigned int> aIndices;
	MESHTYPE type = MESHTYPE::TRIANGLES;


	void Print()
	{
		int i = 0;
		for (auto a : aIndices)
		{
			std::cout << a << " ";
			i++;
			if (i == 6)
			{
				i = 0;
				std::cout << std::endl;
			}
		}
	}
};

class CMesh
{
public:
	static CMesh* CreatePlane();
	static CMesh* CreateTilablePlane(int width, int height);
	static CMesh* CreateCircle();
	static CMesh * CreateCube();
	static CMesh* CreateRectangle();
public:
	CMesh(const SMeshData * pData);
	void Bind();
	void UnBind();
	void Render();
private:
	void LoadMesh(const SMeshData * pData);
private:
	unsigned int m_IDMesh;
	unsigned int m_iIndexCount;
	SMeshData::MESHTYPE m_meshType;
};





