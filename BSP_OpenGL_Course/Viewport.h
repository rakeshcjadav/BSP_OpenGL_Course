#pragma once

class CViewport
{
public:
    CViewport(int width, int height);
    float GetAspectRatio() const;
private:
    int m_iWidth;
    int m_iHeight;
};