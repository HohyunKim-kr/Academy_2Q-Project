#pragma once
#include "Renderer.h"
#include "Collider.h"
class Transform;
class Texture;
class AABB;
class ImageUIRenderer : virtual public Renderer, virtual public Collider
{
public:
	ImageUIRenderer();
	virtual ~ImageUIRenderer();

	Texture* m_pTexture = nullptr;

	std::wstring m_strTextureFilePath;
	D2D1_RECT_F m_SrcRect = { 0.f, 0.f };		// D2D1Bitmap�� Source ����
	D2D1_RECT_F m_DstRect = { 0.f, 0.f };		// RenderTarget�� Destination ����

	bool m_flipX;
	bool m_flipY;

	float alpha = 1.0f;
	float slideBar = 1.0f;

	D2D1_MATRIX_3X2_F	m_ImageTransform;	// �ݴ� �������� ������ ���� ��� Scale.x = -1.0f 

	void LoadTexture(const std::wstring strFilePath);
	void Update(float deltaTime);
	void Render(ID2D1HwndRenderTarget* pRenderTarget, D2D1_MATRIX_3X2_F cameraMat);
	void Render(D2D1_MATRIX_3X2_F cameraMat);

	AABB GetBound();

	// Collider��(��) ���� ��ӵ�
	bool isCollide(Collider* collider, Vector2& resolution) override;
	bool isCollide(const Vector2& point) override;
};

