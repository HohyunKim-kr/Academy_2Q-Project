#include "pch.h"
#include "Transform.h"


void Transform::UpdateTrasnform()
{

	if (type == Type::World)
	{
		m_RelativeTransform =
			//D2D1::Matrix3x2F::Translation(m_CenterTransform.x, m_CenterTransform.y) *     // ��� �����ܰ迡�� ���� ����ؾ� ����. ��������Ʈ �ǹ�
			D2D1::Matrix3x2F::Scale(D2D1::SizeF(m_RelativeScale.x, m_RelativeScale.y)) *
			D2D1::Matrix3x2F::Rotation(m_RelativeRotation) *
			D2D1::Matrix3x2F::Translation(m_RelativeLocation.x, m_RelativeLocation.y);
	}
	else
	{
		m_RelativeTransform =
			//D2D1::Matrix3x2F::Translation(m_CenterTransform.x, m_CenterTransform.y) *     // ��� �����ܰ迡�� ���� ����ؾ� ����. ��������Ʈ �ǹ�
			D2D1::Matrix3x2F::Scale(D2D1::SizeF(m_RelativeScale.x, m_RelativeScale.y)) *
			D2D1::Matrix3x2F::Rotation(m_RelativeRotation) *
			D2D1::Matrix3x2F::Translation({(pos.rectposition.leftBottom.x + pos.rectposition.rightTop.x) /2,
				(pos.rectposition.leftBottom.y + pos.rectposition.rightTop.y) / 2 } );
	}

	// ���� ���� ������� �������� ��Ʈ������ ������ �ְ� (pivot, scale, rotation) �� ���� transform�� matrix�� ���Ͽ� ǥ���ؾ� �ҰŰ���.

	if (m_pParentScene != nullptr)
		m_WorldTransform = m_RelativeTransform * m_pParentScene->m_WorldTransform;
	else
		m_WorldTransform = m_RelativeTransform;
}