#include "Turret.h"
#include "BulletFactory.h"
#include "Bullet.h"
#include"../D2DEngine/GameObject.h"
#include "../D2DEngine/Transform.h"
void Turret::Init()
{
	__super::Init();
}

void Turret::Update(float delta)
{
    __super::Update(delta);
    // �Ѿ��� �߻��� ������ �����Ǹ� �߻�
    if (timeSinceLastShot >= shootCooldown)
    {
        Shoot();
        timeSinceLastShot = 0.0f;  // Ÿ�̸� �ʱ�ȭ
    }
}

void Turret::Shoot()
{
    if (bulletFactory)
    {
        // BulletFactory���� Bullet�� �����´�
        Bullet* bullet = bulletFactory->GetBulletFromPool();

        // �Ѿ� �ʱ�ȭ (�ӵ��� ���� ����)
        Vector2 shootDirection = { 1.0f, 0.0f };  // ���� ��� ���������� �߻�
        float bulletSpeed = 500.0f;
        bullet->Init(bulletSpeed, shootDirection);

        // �Ѿ��� ��ġ�� MusKetShooter�� ��ġ�� ����
        bullet->gameObject->transform->pos.worldPosition = {gameObject->transform->m_WorldTransform.dx, gameObject->transform->m_WorldTransform.dy };
    }
}
