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
    m_verticalVelocity -= m_gravity * delta;
    y += m_verticalVelocity * delta;

    //std::cout << "m_verticalVelocity : " << m_verticalVelocity << std::endl;
    // �� ��ġ ����
    gameObject->transform->pos.worldPosition = { x + speedX, y };
}

void SideMovement::AddForce(Vector2 velocity)
{
    m_verticalVelocity = velocity.y;

    float movespeed = velocity.Length();
    m_speed = movespeed;
    velocity.Normalize();
    m_direction = velocity;
}
