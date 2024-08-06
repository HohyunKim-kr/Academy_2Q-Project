#pragma once
#include "Component.h"
#include "Vector.h"
enum Type
{
	World,
	Ui
};

struct RectPostion
{
	Vector2 leftBottom;
	Vector2 rightTop;
};

union Position
{
	RectPostion rectposition;
	Vector2 worldPosition;
};

class Transform : public Component
{
public:
	Transform() {};
	virtual ~Transform() {};

public:
	Transform*			m_pParentScene = nullptr;	// �θ� Scene ������Ʈ	
	Vector2		m_RelativeScale = { 1,1 };	// ��� ũ��
	float				m_RelativeRotation = 0;		// ��� ȸ��
	//Vector2 		m_RelativeLocation = { 0,0 }; // ��� ��ġ
	D2D1_MATRIX_3X2_F	m_RelativeTransform;		// ��� ���� ��ȯ
	D2D1_MATRIX_3X2_F	m_WorldTransform;			// �θ���� �ݿ��� ���� ��ȯ
	Type type = Type::World;
	Position pos;
	//Vector2		m_CenterTransform;

	// RelativeTransform�� m_WorldTransform�� ����Ѵ�.
	void UpdateTrasnform();
	void SetParent(Transform* pParentScene) { m_pParentScene = pParentScene; }
};

