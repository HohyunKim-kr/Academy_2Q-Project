#pragma once
#include "Renderer.h"
#include "EventSystem.h"
#include <functional>
#include "Collider.h"
class Texture;

class Button : virtual public Renderer, virtual public Collider, public IPointer
{
public:
	Button() {};
	virtual ~Button();

	// Renderer��(��) ���� ��ӵ�
	AABB GetBound() override;
	void Render(D2D1_MATRIX_3X2_F cameraMat) override;
	void Render(ID2D1HwndRenderTarget* pRenderTarget, D2D1_MATRIX_3X2_F cameraMat) override;

	// IPointer��(��) ���� ��ӵ�
	void IPointerEnter() override;
	void IPointerStay() override;
	void IPointerExit() override;

	Texture* m_pTexture = nullptr;

	std::wstring m_strTextureFilePath;
	D2D1_RECT_F m_SrcRect = { 0.f, 0.f };		// D2D1Bitmap�� Source ����
	D2D1_RECT_F m_DstRect = { 0.f, 0.f };		// RenderTarget�� Destination ����

	D2D1_MATRIX_3X2_F	m_ImageTransform;	// �ݴ� �������� ������ ���� ��� Scale.x = -1.0f 

	void LoadTexture(const std::wstring strFilePath);
	void Update(float deltaTime);

private:
	bool isMouseOn = false;
	bool isClicked = false;
	std::function<void()> events;
public:

	void OnClick();
	void OffClick();
	void AddListener(std::function<void()> func);

	// Collider��(��) ���� ��ӵ�
	bool isCollide(Collider* collider, Vector2& resolution) override;
	bool isCollide(const Vector2& point) override;
};

