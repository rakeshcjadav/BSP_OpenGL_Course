#pragma once

class CCamera;

class CViewport
{
public:
	CViewport(int posX, int posY, int width, int height);
	float GetAspectRatio() const;
	int GetWidth() const;
	int GetHeight() const;
	void Clear(glm::vec4 color);
	void Update(CCamera* pCamera);
private:
	int m_posX;
	int m_posY;
	int m_iWidth;
	int m_iHeight;
};