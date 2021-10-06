#include"MeshRenderer.h"
#include"Camera.h"
#include"Mesh.h"
#include"Light.h"
#include"Material.h"
#include"Transform.h"
#include"Model.h"
#include<typeinfo>

CMeshRenderer::CMeshRenderer()
{

}

void CMeshRenderer::Render(CMesh* pMesh, CTransform* pTransform, const CMaterial* pMaterial, CCamera* pCamera, 
    std::list<CLight*>* pDirectionalLights,
    std::list<CLight*>* pPointLights,
    std::list<CLight*>* pSpotLights)
{
    pMesh->Bind();
    {
        pMaterial->Bind();
        {
            float currentTime = 0.0f;// (float)glfwGetTime();
            float fScale = 0.1f + 1.5f * fabsf(sinf(0.05f * currentTime));
            float fSineTime = 1.0f * sinf(currentTime);
            
            pMaterial->SetUniform("Scale", fScale);
            pMaterial->SetUniform("SineTime", fSineTime);

            glm::mat4 transformMat = pTransform->GetTransform();
            glm::mat4 normalMat = glm::transpose(glm::inverse(transformMat));

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

void CMeshRenderer::Render(CModel* pModel, CTransform* pTransform, CCamera* pCamera,
    std::list<CLight*>* pDirectionalLights,
    std::list<CLight*>* pPointLights,
    std::list<CLight*>* pSpotLights)
{
    CMaterial* pMaterial = pModel->GetMaterial();
    pMaterial->Bind();
    {
        glm::mat4 transformMat = pTransform->GetTransform();
        glm::mat4 normalMat = glm::transpose(glm::inverse(transformMat));

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
    
    pModel->Render();
}