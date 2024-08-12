#include "MusKetShooter.h"
#include "Bullet.h"
#include "BulletFactory.h"
#include "../D2DEngine/Scene.h"
#include"../D2DEngine/GameObject.h"
#include "../D2DEngine/Transform.h"

//MusKetShooter::MusKetShooter(Scene* scene)
//{
//    // BulletFactory�� �ʱ�ȭ (Scene�� ����)
//}

void MusKetShooter::Init()
{
    //// BombCart Ư�� �ʱ�ȭ -> ��ġ ���� �ؾ���
    //SetStat(16, 5.0f, 10, 3.0f, 240);
    //SetResist(0, 0, 0, 0);
    //SetReward(50, 10);

    //eliteType = EliteType::Normal; // �⺻ ����Ʈ Ÿ�� ���� (Normal)
}

void MusKetShooter::Update(float delta)
{
    __super::Update(delta);

    //timeSinceLastShot += delta;

    //// �Ѿ��� �߻��� ������ �����Ǹ� �߻�
    //if (timeSinceLastShot >= shootCooldown)
    //{
    //    Shoot();
    //    timeSinceLastShot = 0.0f;  // Ÿ�̸� �ʱ�ȭ
    //}

    // ��Ÿ ������Ʈ �ڵ� �߰�
}

void MusKetShooter::Render(D2D1_MATRIX_3X2_F cameraMat)
{
    __super::Render(cameraMat);
    // ������ ���� �߰� �ڵ�
}

void MusKetShooter::Shoot()
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
        bullet->gameObject->transform->pos.worldPosition = gameObject->transform->pos.worldPosition;
    }
}
