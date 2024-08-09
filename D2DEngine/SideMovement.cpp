#include "pch.h"
#include "SideMovement.h"
#include "GameObject.h"
#include "Transform.h"

void SideMovement::Update(float delta)
{
    // ���� ��ġ ��������
    float x = gameObject->transform->pos.worldPosition.x;
    float y = gameObject->transform->pos.worldPosition.y;

    // ���� �̵� ���
    float speedX = m_direction.x * m_speed * delta;

    // ���� �ӵ� ������Ʈ (�߷� ����)
    m_verticalVelocity += m_gravity * delta;
    y -= m_verticalVelocity * delta;

    // �� ��ġ ����
    gameObject->transform->pos.worldPosition = { x + speedX, y };
}
