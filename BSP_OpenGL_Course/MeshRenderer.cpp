#include"pch.h"
#include"MeshRenderer.h"
#include"Camera.h"
#include"Mesh.h"
#include"Light.h"
#include"Material.h"
#include"MaterialPass.h"
#include"Transform.h"
#include"Model.h"


CMeshRenderer::CMeshRenderer()
{

}

void CMeshRenderer::Render(CMesh* pMesh, CTransform* pTransform, const CMaterialPass* pMaterial, CCamera* pCamera, 
	std::list<CLight*>* pDirectionalLights,
	std::list<CLight*>* pPointLights,
	std::list<CLight*>* pSpotLights)
{
	pMesh->Bind();
	{
		pMaterial->Bind();
		{
			glm::mat4 transformMat = pTransform->GetTransform();
			glm::mat4 normalMat = glm::transpose(glm::inverse(glm::mat3(transformMat)));

			// Camera
			glm::mat4 cameraMat = pCamera->GetViewMatrix();
			glm::mat4 projectionMat = pCamera->GetProjectionMatrix();
			glm::vec3 cameraPos = pCamera->GetPosition();
			pMaterial->SetUniform("TransformMat", transformMat);
			pMaterial->SetUniform("NormalMat", normalMat);
			pMaterial->SetUniform("CameraMat", cameraMat);
			pMaterial->SetUniform("ProjectionMat", projectionMat);
			pMaterial->SetUniform("CameraPos", cameraPos);

			// Light
			if (pDirectionalLights)
			{
				for (CLight* pLight : *(pDirectionalLights))
				{
					pLight->Bind(pMaterial, 0);
				}
			}

			if (pPointLights)
			{
				int i = 0;
				pMaterial->SetUniform("PointLightCount", (int)pPointLights->size());
				for (CLight* pLight : *(pPointLights))
				{
					pLight->Bind(pMaterial, i++);
				}
			}

			if (pSpotLights)
			{
				int i = 0;
				pMaterial->SetUniform("SpotLightCount", (int)pSpotLights->size());
				for (CLight* pLight : *(pSpotLights))
				{
					pLight->Bind(pMaterial, i++);
				}
			}
		}
	}
	pMesh->Render();
	pMesh->UnBind();
}

void CMeshRenderer::Render(const CModel* pModel, CTransform* pTransform, CCamera* pCamera,
	std::list<CLight*>* pDirectionalLights,
	std::list<CLight*>* pPointLights,
	std::list<CLight*>* pSpotLights,
	bool bShadowCasterPass)
{
	const CMaterial* pMaterial = pModel->GetMaterial();
	const CMaterialPass * pPass = pMaterial->GetPass(bShadowCasterPass ? 0 : 1);
	pPass->Bind();
	{
		glm::mat4 transformMat = pTransform->GetTransform();
		glm::mat4 normalMat = glm::transpose(glm::inverse(transformMat));

		// Camera
		glm::mat4 cameraMat = pCamera->GetViewMatrix();
		glm::mat4 projectionMat = pCamera->GetProjectionMatrix();
		glm::vec3 cameraPos = pCamera->GetPosition();
		pPass->SetUniform("TransformMat", transformMat);
		pPass->SetUniform("NormalMat", normalMat);
		pPass->SetUniform("CameraMat", cameraMat);
		pPass->SetUniform("ProjectionMat", projectionMat);
		pPass->SetUniform("CameraPos", cameraPos);

		// Light
		if (pDirectionalLights)
		{
			for (CLight* pLight : *(pDirectionalLights))
			{
				pLight->Bind(pPass, 0);
			}
		}

		if (pPointLights)
		{
			int i = 0;
			pMaterial->SetUniform("PointLightCount", (int)pPointLights->size());
			for (CLight* pLight : *(pPointLights))
			{
				pLight->Bind(pPass, i++);
			}
		}

		if (pSpotLights)
		{
			int i = 0;
			pMaterial->SetUniform("SpotLightCount", (int)pSpotLights->size());
			for (CLight* pLight : *(pSpotLights))
			{
				pLight->Bind(pPass, i++);
			}
		}
	}
	
	pModel->Render();
}