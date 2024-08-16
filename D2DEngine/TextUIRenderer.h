#pragma once
#include "Renderer.h"
#include "Collider.h"
class Transform;
class Texture;
class AABB;
class TextUIRenderer : virtual public Renderer, virtual public Collider
{
private:
	IDWriteTextFormat* pTextFormat = nullptr;
public:
	TextUIRenderer();
	virtual ~TextUIRenderer();

	D2D1_RECT_F m_SrcRect = { 0.f, 0.f };		// D2D1Bitmap�� Source ����
	D2D1_RECT_F m_DstRect = { 0.f, 0.f };		// RenderTarget�� Destination ����
	
	std::wstring text = L"";

	ID2D1SolidColorBrush* color_brush = nullptr;
	D2D1::ColorF color = D2D1::ColorF::Black;

	D2D1_MATRIX_3X2_F	m_ImageTransform;	// �ݴ� �������� ������ ���� ��� Scale.x = -1.0f 

	void Update(float deltaTime);
	void Render(ID2D1HwndRenderTarget* pRenderTarget, D2D1_MATRIX_3X2_F cameraMat);
	void Render(D2D1_MATRIX_3X2_F cameraMat);

	AABB GetBound();

	// Collider��(��) ���� ��ӵ�
	bool isCollide(Collider* collider, Vector2& resolution) override;
	bool isCollide(const Vector2& point) override;

	void SetTextColor(D2D1::ColorF _color);
	void SetFontSize(float size);
};

