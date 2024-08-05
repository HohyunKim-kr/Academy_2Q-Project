#pragma once
#include "Collider.h"
#include "Renderer.h"
class CircleCollider : public Collider, public Renderer
{
protected:
	float radius;

public:
	CircleCollider(CollisionType cType = BLOCK) {
		m_ColliderType = ColliderType::Circle;
		m_CollisionType = cType;
	}

	// Collider��(��) ���� ��ӵ�
	bool isCollide(Collider* collider, Vector2& resolution) override;

	float GetRadius() { return radius; }

	// Renderer��(��) ���� ��ӵ�
	AABB GetBound() override;
	void Render(D2D1_MATRIX_3X2_F cameraMat) override;
	void Render(ID2D1HwndRenderTarget* pRenderTarget, D2D1_MATRIX_3X2_F cameraMat) override;
};

