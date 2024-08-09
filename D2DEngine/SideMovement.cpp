#include "pch.h"
#include "SideMovement.h"
#include "GameObject.h"
#include "Transform.h"

void SideMovement::Update(float delta)
{
    // �߷� ȿ���� ������ ���� �̵� ó��
    float x = gameObject->transform->pos.worldPosition.x;
    float y = gameObject->transform->pos.worldPosition.y;

    // Y�� �̵��� �����Ͽ� ����(����) �̵��� ó��
    float speedX = m_direction.x * m_speed * delta;

    gameObject->transform->pos.worldPosition = { x + speedX, y };
}
