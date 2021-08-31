#include"Viewport.h"
#include"OpenGL.h"

CViewport::CViewport(int width, int height)
{
    m_iWidth = width;
    m_iHeight = height;

    glViewport(0, 0, m_iWidth, m_iHeight);
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