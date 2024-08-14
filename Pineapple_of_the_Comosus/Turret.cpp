#include "Turret.h"
#include "BulletFactory.h"
#include "MainPineApple.h"
#include "Bullet.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/SpriteRenderer.h"
#include "DynamicData.h"
void Turret::Init()
{
    auto data = dynamicData->GetStaticTurretData(turretType);
    auto rewardData = dynamicData->GetRewardTurretData(turretType);
    float shootTimer = data->fireRate + rewardData.fireRate;

    timeSinceLastShot = 0.f;
}

void Turret::Update(float delta)
{
    __super::Update(delta);
    // �Ѿ��� �߻��� ������ �����Ǹ� �߻�
    auto data = dynamicData->GetStaticTurretData(turretType);
    auto rewardData = dynamicData->GetRewardTurretData(turretType);
    float shootTimer = data->fireRate + rewardData.fireRate;
    shootTimer = 1.f / shootTimer;

    timeSinceLastShot += delta;

    if (timeSinceLastShot >= shootTimer)
    {
        Shoot();
        timeSinceLastShot -= shootTimer;  // Ÿ�̸� �ʱ�ȭ
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

        auto data = dynamicData->GetStaticTurretData(turretType);//DataManager::GetInstance().GetTurretData((int)turretType);
        auto rewardData = dynamicData->GetRewardTurretData(turretType);
        //float bulletSpeed = 1000.0f;
        //bullet->Init(bulletSpeed, shootDirection);
        bullet->SetAttackValue(shootDirection, 
            data->burstRange + rewardData.burstRange,
            data->damage + rewardData.damage,
            data->penetration + rewardData.penetration,
            data->bulletSpeed + rewardData.bulletSpeed,
            data->slowRate + rewardData.slowRate,
            data->slowDuration + rewardData.slowDuration,
            static_cast<BulletType>(data->bulletType));
        bullet->gameObject->GetComponent<SpriteRenderer>()->LoadTexture(data->bulletImagePath);
    }
}
