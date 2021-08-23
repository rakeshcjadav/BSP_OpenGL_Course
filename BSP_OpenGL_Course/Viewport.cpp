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