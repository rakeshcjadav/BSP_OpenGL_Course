#include"pch.h"
#include"Viewport.h"
#include"Camera.h"

CViewport::CViewport(int posX, int posY, int width, int height)
{
    m_posX = posX;
    m_posY = posY;
    m_iWidth = width;
    m_iHeight = height;
}

float CViewport::GetAspectRatio() const
{
    return (float)m_iWidth / (float)m_iHeight;
}

int CViewport::GetWidth() const
{
    return m_iWidth;
}

int CViewport::GetHeight() const
{
    return m_iHeight;
}

void CViewport::Clear(glm::vec4 color)
{
    glViewport(m_posX, m_posY, m_iWidth, m_iHeight);
    glScissor(m_posX, m_posY, m_iWidth, m_iHeight);
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void CViewport::Update(CCamera* pCamera)
{
    pCamera->Assign(this);
    pCamera->Update();
}