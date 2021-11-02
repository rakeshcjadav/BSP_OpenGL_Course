#pragma once

class CFrameBuffer
{
public:
    CFrameBuffer(glm::uvec2 size);

    void Bind();
    void UnBind();
private:
    unsigned int m_IDFrameBuffer;
    glm::uvec2 m_Size;
    glm::ivec4 m_ViewportSize;
};
