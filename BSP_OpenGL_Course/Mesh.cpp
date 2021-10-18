#include"pch.h"
#include"Mesh.h"

// static 
// Plane
CMesh* CMesh::CreatePlane()
{
	// Local Positions of vertices
	SMeshData meshData;
	meshData.aVertices.push_back(SVertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)));
	meshData.aVertices.push_back(SVertex(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)));
	meshData.aVertices.push_back(SVertex(glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)));
	meshData.aVertices.push_back(SVertex(glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)));

	meshData.aIndices = {
		0, 1, 3, 2
	};

	for (unsigned int i = 0; i < meshData.aIndices.size() - 2; i++)
	{
		SVertex& v1 = meshData.aVertices[meshData.aIndices[i]];
		SVertex& v2 = meshData.aVertices[meshData.aIndices[i+1]];
		SVertex& v3 = meshData.aVertices[meshData.aIndices[i+2]];
		glm::vec3 edge1 = v2.position - v1.position;
		glm::vec3 edge2 = v3.position - v1.position;

		glm::vec2 deltaUV1 = v2.uv - v1.uv;
		glm::vec2 deltaUV2 = v3.uv - v1.uv;

		float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

		v1.tangent.x += f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
		v1.tangent.y += f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
		v1.tangent.z += f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

		v1.bitangent.x += f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
		v1.bitangent.y += f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
		v1.bitangent.z += f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);

		v1.tangent = glm::normalize(v1.tangent);
		v2.tangent = v1.tangent;
		v3.tangent = v1.tangent;

		v1.bitangent = glm::normalize(v1.bitangent);
		v2.bitangent = v1.bitangent;
		v3.bitangent = v1.bitangent;
	}

	meshData.type = SMeshData::MESHTYPE::TRIANGLE_STRIP;

	return new CMesh(&meshData);
}

// Terrain
CMesh* CMesh::CreateTilablePlane(int width, int height)
{
	SMeshData meshData;
	for (int y = 0; y <= height; y++)
	{
		for (int x = 0; x <= width; x++)
		{
			SVertex vertex = SVertex(glm::vec3(x - width / 2.0f, y - height / 2.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(x, y));
			vertex.tangent = glm::vec3(1.0f, 0.0f, 0.0f);
			vertex.bitangent = glm::vec3(0.0f, -1.0f, 0.0f);
			meshData.aVertices.push_back(vertex);
			if (x == width || y == height)
				continue;

			meshData.aIndices.push_back(x + y * width + y);
			meshData.aIndices.push_back((x + 1) + y * width + y);
			meshData.aIndices.push_back(x + (y + 1) * width + (y + 1));

			meshData.aIndices.push_back((x + 1) + y * width + y);
			meshData.aIndices.push_back((x + 1) + (y + 1) * width + (y + 1));
			meshData.aIndices.push_back(x + (y + 1) * width + (y + 1));
		}
	}

	/*
	for (unsigned int i = 0; i < meshData.aIndices.size(); i = i + 3)
	{
		SVertex& v1 = meshData.aVertices[meshData.aIndices[i]];
		SVertex& v2 = meshData.aVertices[meshData.aIndices[i + 1]];
		SVertex& v3 = meshData.aVertices[meshData.aIndices[i + 2]];
		glm::vec3 edge1 = v2.position - v1.position;
		glm::vec3 edge2 = v3.position - v1.position;

		glm::vec2 deltaUV1 = v2.uv - v1.uv;
		glm::vec2 deltaUV2 = v3.uv - v1.uv;

		float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

		v1.tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
		v1.tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
		v1.tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

		v1.bitangent.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
		v1.bitangent.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
		v1.bitangent.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);

		v1.tangent = glm::normalize(v1.tangent);
		v2.tangent = v1.tangent;
		v3.tangent = v1.tangent;

		v1.bitangent = glm::normalize(v1.bitangent);
		v2.bitangent = v1.bitangent;
		v3.bitangent = v1.bitangent;
	}*/

	meshData.type = SMeshData::MESHTYPE::TRIANGLES;

	return new CMesh(&meshData);
}

// Circle
CMesh* CMesh::CreateCircle()
{
	// Local Positions of vertices
	SMeshData meshData;
	SVertex vertex(glm::vec3(0.5f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.5f, 0.0f));
	meshData.aVertices.push_back(SVertex(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.5f, 0.5f)));
	meshData.aIndices.push_back(0);
	int circle = 360;
	int sides = 72;
	int division = circle / sides;
	for (int angle = 0, index = 1; angle <= circle; index++, angle+=division)
	{
		glm::vec3 angles(0.0f, 0.0f, angle);
		glm::mat3 mat = glm::toMat3(glm::quat(glm::radians(angles)));

		glm::vec3 pos = mat * vertex.position;
		glm::vec3 normal = mat * vertex.normal;
		glm::vec3 tex = mat * glm::vec3(vertex.uv, 1.0f);

		meshData.aVertices.push_back(SVertex(pos, normal, glm::vec2(tex)+glm::vec2(0.5f, 0.5f)));
		meshData.aIndices.push_back(index);
	}

	meshData.type = SMeshData::MESHTYPE::TRIANGLE_FAN;

	return new CMesh(&meshData);
}

// Cube
CMesh* CMesh::CreateCube()
{
	// Local Positions of vertices
	SMeshData meshData;

	std::vector<SVertex> tempVertices;
	tempVertices.push_back(SVertex(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)));
	tempVertices.push_back(SVertex(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)));
	tempVertices.push_back(SVertex(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)));
	tempVertices.push_back(SVertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)));

	meshData.aIndices = {
		0, 1, 2,
		2, 3, 0,
	};

	std::vector<glm::vec3> angles;
	angles.push_back(glm::vec3(0.0f, 0.0f, 0.0f)); // Front
	angles.push_back(glm::vec3(-90.0f, 0.0f, 0.0f)); // Top
	angles.push_back(glm::vec3(-180.0f, 0.0f, 0.0f)); // Back
	angles.push_back(glm::vec3(-270.0f, 0.0f, 0.0f)); // Bottom
	angles.push_back(glm::vec3(0.0f, 90.0f, 0.0f)); // Left
	angles.push_back(glm::vec3(0.0f, -90.0f, 0.0f)); // Right

	int face = 0;
	int facevertex = 4;
	for (const auto & angle : angles)
	{
		glm::mat3 mat = glm::toMat3(glm::quat(glm::radians(angle)));
		for (const SVertex & vertex : tempVertices)
		{
			glm::vec3 pos = mat * vertex.position;
			glm::vec3 normal = mat * vertex.normal;
			meshData.aVertices.push_back(SVertex(pos, normal, vertex.uv));
		}
		meshData.aIndices.push_back(face * facevertex);
		meshData.aIndices.push_back(face * facevertex + 1);
		meshData.aIndices.push_back(face * facevertex + 2);
		meshData.aIndices.push_back(face * facevertex + 2);
		meshData.aIndices.push_back(face * facevertex + 3);
		meshData.aIndices.push_back(face * facevertex);
		face++;
	}

	for (unsigned int i = 0; i < meshData.aIndices.size(); i=i+3)
	{
		SVertex& v1 = meshData.aVertices[meshData.aIndices[i]];
		SVertex& v2 = meshData.aVertices[meshData.aIndices[i + 1]];
		SVertex& v3 = meshData.aVertices[meshData.aIndices[i + 2]];
		glm::vec3 edge1 = v2.position - v1.position;
		glm::vec3 edge2 = v3.position - v1.position;

		glm::vec2 deltaUV1 = v2.uv - v1.uv;
		glm::vec2 deltaUV2 = v3.uv - v1.uv;

		float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

		v1.tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
		v1.tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
		v1.tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

		v1.bitangent.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
		v1.bitangent.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
		v1.bitangent.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);

		v1.tangent = glm::normalize(v1.tangent);
		v2.tangent = v1.tangent;
		v3.tangent = v1.tangent;

		v1.bitangent = glm::normalize(v1.bitangent);
		v2.bitangent = v1.bitangent;
		v3.bitangent = v1.bitangent;
	}

	meshData.type = SMeshData::MESHTYPE::TRIANGLES;

	return new CMesh(&meshData);
}

CMesh* CMesh::CreateRectangle()
{
	// Local Positions of vertices
	SMeshData meshData;
	meshData.aVertices.push_back(SVertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)));
	meshData.aVertices.push_back(SVertex(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)));
	meshData.aVertices.push_back(SVertex(glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)));
	meshData.aVertices.push_back(SVertex(glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)));

	meshData.aIndices = {
		0, 1, 2, 3
	};

	meshData.type = SMeshData::MESHTYPE::LINE_STRIP;

	return new CMesh(&meshData);
}

CMesh::CMesh(const SMeshData* pData)
{
	LoadMesh(pData);
}

void CMesh::Bind()
{
	glBindVertexArray(m_IDMesh);
}

void CMesh::UnBind()
{
	glBindVertexArray(0);
}

void CMesh::Render()
{
	glDrawElements(static_cast<int>(m_meshType), m_iIndexCount, GL_UNSIGNED_INT, nullptr);
}

void CMesh::LoadMesh(const SMeshData* pData)
{
	//LogMessage(std::format("aVertices : {0}", sizeof(SVertex) * pData->aVertices.size()));
	//LogMessage(std::format("aIndices : {0}", sizeof(unsigned int) * pData->aIndices.size()));
	
	m_meshType = pData->type;
	m_iIndexCount = pData->aIndices.size();

	glGenVertexArrays(1, &m_IDMesh);
	glBindVertexArray(m_IDMesh);
	{
		unsigned int VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(SVertex) * pData->aVertices.size() /* Bytes */, &(pData->aVertices.front()), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SVertex), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(SVertex), (void*)(sizeof(glm::vec3)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(SVertex), (void*)(2*sizeof(glm::vec3)));
		glEnableVertexAttribArray(2);

		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(SVertex), (void*)(3*sizeof(glm::vec3)));
		glEnableVertexAttribArray(3);

		glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(SVertex), (void*)(4*sizeof(glm::vec3)));
		glEnableVertexAttribArray(4);

		unsigned int EBO;
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * pData->aIndices.size() /* Bytes */, &(pData->aIndices.front()), GL_STATIC_DRAW);
	}
	glBindVertexArray(0);
}