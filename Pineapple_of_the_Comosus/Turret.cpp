#include "Turret.h"
#include "BulletFactory.h"
#include "MainPineApple.h"
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
    timeSinceLastShot += delta;

    if (timeSinceLastShot >= shootCooldown)
    {
        Shoot();
        timeSinceLastShot = 0.0f;  // Ÿ�̸� �ʱ�ȭ
    }
}

void Turret::Shoot()
{
    if (parentPineApple->bulletFactory)
    {
        // BulletFactory���� Bullet�� �����´�
        Bullet* bullet = parentPineApple->bulletFactory->GetBulletFromPool();
        // �Ѿ��� ��ġ�� MusKetShooter�� ��ġ�� ����
        bullet->gameObject->transform->pos.worldPosition = {gameObject->transform->m_WorldTransform.dx, gameObject->transform->m_WorldTransform.dy };

        // �Ѿ� �ʱ�ȭ (�ӵ��� ���� ����)
        Vector2 shootDirection = { 1.0f, 0.0f };  // ���� ��� ���������� �߻�

        float angle = gameObject->transform->m_RelativeRotation;
        shootDirection.x = std::cosf(angle / 180.f * 3.14159f);
        shootDirection.y = std::sinf(angle / 180.f * 3.14159f);

        auto data = DataManager::GetInstance().GetTurretData((int)turretType);
        //float bulletSpeed = 1000.0f;
        //bullet->Init(bulletSpeed, shootDirection);
        bullet->SetAttackValue(shootDirection, data->burstRange, data->damage, data->penetration, data->bulletSpeed, data->slowRate, data->slowDuration);

    }
}
