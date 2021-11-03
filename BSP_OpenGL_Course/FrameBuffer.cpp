#include"pch.h"
#include"FrameBuffer.h"
#include"AssetManager.h"
#include"Texture.h"

CFrameBuffer::CFrameBuffer(glm::uvec2 size)
{
    m_Size = size;
    glGenFramebuffers(1, &m_IDFrameBuffer);

    const CTexture* pTexture = CAssetManager::Get().GetTexture("shadow");

    // Attachment
    glBindFramebuffer(GL_FRAMEBUFFER, m_IDFrameBuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, pTexture->GetID(), 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void CFrameBuffer::Bind()
{
    glGetIntegerv(GL_VIEWPORT, glm::value_ptr(m_ViewportSize));
    glViewport(0, 0, m_Size.x, m_Size.y);
    glScissor(0, 0, m_Size.x, m_Size.y);
    glBindFramebuffer(GL_FRAMEBUFFER, m_IDFrameBuffer);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void CFrameBuffer::UnBind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(m_ViewportSize.x, m_ViewportSize.y, m_ViewportSize.z, m_ViewportSize.w);
    glScissor(m_ViewportSize.x, m_ViewportSize.y, m_ViewportSize.z, m_ViewportSize.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}