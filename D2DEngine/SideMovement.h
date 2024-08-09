#pragma once
#include "Movement.h"

class SideMovement : public Movement
{
private:
    float m_gravity = 500.f;  // �߷��� ����
    float m_verticalVelocity = 0.0f; // ���� �ӵ�
public:
    void Update(float delta) override;
    void AddForce(Vector2 velocity);
};
