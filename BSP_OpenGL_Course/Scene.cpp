#include"pch.h"
#include"Scene.h"
#include"Material.h"
#include"Camera.h"
#include"PointLight.h"
#include"DirectionalLight.h"
#include"SpotLight.h"
#include"GameObject.h"
#include"Texture.h"
#include"Program.h"
#include"Transform.h"
#include"Mesh.h"
#include"MeshRenderer.h"
#include"Model.h"

CScene::CScene()
{

}

void CScene::Update(CCamera* pCamera)
{
	for (CGameObject* pGameObject : m_listGameObjects)
	{
		pGameObject->Update();
		pGameObject->Render(pCamera, &m_listDirectionalLights, &m_listPointLights, &m_listSpotLights);
	}
}

void CScene::LoadScene()
{
	CreateGameObjects();
	CreateCameras();
	CreateLights();
}

CCamera* CScene::GetCamera(std::string strName)
{
	return m_mapCameras[strName];
}

void CScene::CreateGameObjects()
{
	CMeshRenderer* pMeshRenderer = new CMeshRenderer();
	CMesh* pPlaneMesh = CMesh::CreatePlane();
	CMesh* pCubeMesh = CMesh::CreateCube();
	CModel* pModel = CModel::LoadModel("backpack/backpack.obj");
	// Ground Plane
	{
		CTransform* pTransform = new CTransform(glm::vec3(0.0f), glm::vec3(-90.0f, 0.0f, 0.0f), glm::vec3(100.0f));
		CGameObject* pObject = new CGameObject(pTransform, nullptr, pPlaneMesh, pMeshRenderer, CAssetManager::Get().GetMaterial("lit_orange"));
		m_listGameObjects.push_back(pObject);
	}
	// Back Wall
	{
		CTransform* pTransform = new CTransform(glm::vec3(0.0f, 5.0f, -5.0f), glm::vec3(0.0f), glm::vec3(10.0f));
		CGameObject* pObject = new CGameObject(pTransform, pModel, pPlaneMesh, pMeshRenderer, CAssetManager::Get().GetMaterial("lit_orange"));
		m_listGameObjects.push_back(pObject);
	}
	// Front Wall
	{
		CTransform* pTransform = new CTransform(glm::vec3(0.0f, 5.0f, 5.0f), glm::vec3(0.0f, 180.0f, 0.0f), glm::vec3(10.0f));
		CGameObject* pObject = new CGameObject(pTransform, pModel, pPlaneMesh, pMeshRenderer, CAssetManager::Get().GetMaterial("lit_orange"));
		m_listGameObjects.push_back(pObject);
	}
	// Left Wall
	{
		CTransform* pTransform = new CTransform(glm::vec3(-5.0f, 5.0f, 0.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(10.0f));
		CGameObject* pObject = new CGameObject(pTransform, pModel, pPlaneMesh, pMeshRenderer, CAssetManager::Get().GetMaterial("lit_orange"));
		m_listGameObjects.push_back(pObject);
	}
	// Right Wall
	{
		CTransform* pTransform = new CTransform(glm::vec3(5.0f, 5.0f, 0.0f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(10.0f));
		CGameObject* pObject = new CGameObject(pTransform, pModel, pPlaneMesh, pMeshRenderer, CAssetManager::Get().GetMaterial("lit_orange"));
		m_listGameObjects.push_back(pObject);
	}
	// Green Cube
	{
		CTransform* pTransform = new CTransform(glm::vec3(-2.0f, 1.0f, -2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f));
		CGameObject* pObject = new CGameObject(pTransform, pModel, pCubeMesh, pMeshRenderer, CAssetManager::Get().GetMaterial("lit_green"));
		m_listGameObjects.push_back(pObject);
	}
	// Wooden Crate
	{
		CTransform* pTransform = new CTransform(glm::vec3(3.0f, 1.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f));
		CGameObject* pPlane = new CGameObject(pTransform, pModel, pCubeMesh, pMeshRenderer, CAssetManager::Get().GetMaterial("lit_diff_spec"));
		m_listGameObjects.push_back(pPlane);
	}
	// Circle
	{
		CTransform* pTransform = new CTransform(glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f));
		CGameObject* pObject = new CGameObject(pTransform, pModel, CMesh::CreateCircle(), pMeshRenderer, CAssetManager::Get().GetMaterial("unlit_orange"));
		m_listGameObjects.push_back(pObject);
	}
	// Backpack
	{
		CTransform* pTransform = new CTransform(glm::vec3(8.0f, 2.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f));
		CGameObject* pObject = new CGameObject(pTransform, pModel, nullptr, pMeshRenderer, CAssetManager::Get().GetMaterial("lit_orange"));
		m_listGameObjects.push_back(pObject);
	}
}

void CScene::CreateCameras()
{
	SCameraDef* pCameraDef = new SCameraDef();
	pCameraDef->position = glm::vec3(0.0f, 5.0f, 7.0f);
	pCameraDef->direction = glm::normalize(glm::vec3(0.0f, 0.0f, 0.0f) - glm::vec3(0.0f, 5.0f, 7.0f));
	pCameraDef->up = glm::vec3(0.0f, 1.0f, 0.0f);
	pCameraDef->fov = 45.0f;
	pCameraDef->fNearPlane = 0.1f;
	pCameraDef->fFarPlane = 100.0f;
	CCamera * pCamera = new CCamera(pCameraDef, nullptr);
	pCamera->SetScene(this);
	m_mapCameras["MainCamera"] = pCamera;
	CCamera* pCamera2 = new CCamera(pCameraDef, nullptr);
	pCamera2->SetScene(this);
	m_mapCameras["SecondCamera"] = pCamera2;
}

void CScene::CreateLights()
{
	// Directional
	m_listDirectionalLights.push_back(
		new CDirectionalLight(
			glm::normalize(glm::vec3(0.f, -1.0f, -1.f)),
			glm::vec3(0.0f)));

	// Spot
	m_listSpotLights.push_back(
		new CSpotLight(
			glm::vec3(2.f, 2.5f, 2.f),
			glm::normalize(glm::vec3(0.0f, -1.0f, -1.0f)),
			glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(1.0f, 0.05f, 0.001f), 5.0f, 35.0f));

	m_listSpotLights.push_back(
		new CSpotLight(
			glm::vec3(16.f, 5.5f, 2.f),
			glm::normalize(glm::vec3(0.0f, -1.0f, 0.0f)),
			glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.05f, 0.001f), 0.0f, 60.0f));
	
	// Point
	m_listPointLights.push_back(
		new CPointLight(
			glm::vec3(0.f, 5.0f, 6.f),
			glm::vec3(1.0f, 1.0f, 1.0f),
			glm::vec3(1.0f, 0.05f, 0.001f)));
	
	m_listPointLights.push_back(
		new CPointLight(
			glm::vec3(10.f, 4.5f, 1.f),
			glm::vec3(1.0f, 1.0f, 1.0f),
			glm::vec3(1.0f, 0.05f, 0.001f)));
}