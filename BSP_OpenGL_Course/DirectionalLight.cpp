#include"pch.h"
#include"DirectionalLight.h"
#include"MaterialPass.h"

CDirectionalLight::CDirectionalLight(glm::vec3 direction, glm::vec3 color) :
	m_vDirection(0.0f),
	CLight(color)
{
	m_vDirection = glm::normalize(direction);
}

void CDirectionalLight::Bind(const CMaterialPass* pPass, int index)
{
	pPass->SetUniform("directionalLight.direction", m_vDirection);
	pPass->SetUniform("directionalLight.color", m_vColor);
	//glm::mat4 lightViewMat = GetViewMatrix();
	//glm::mat4 lightProjectionMat = GetProjectionMatrix();
	//glm::mat4 lightProjectionViewMat = lightProjectionMat * lightViewMat;
	//pMaterial->SetUniform("LightProjectionViewMat", lightProjectionViewMat);
}

glm::mat4 CDirectionalLight::GetViewMatrix() const
{
	glm::vec3 lightPos = -m_vDirection * 10.0f;
	glm::vec3 target = m_vDirection * 10.0f;
	return glm::lookAt(lightPos, target, glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 CDirectionalLight::GetProjectionMatrix() const
{
	return glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 50.0f);
}