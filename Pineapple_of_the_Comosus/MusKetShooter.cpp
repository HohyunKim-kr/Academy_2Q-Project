#include "MusKetShooter.h"

MusKetShooter::MusKetShooter()
{
    // MusKetShooter Ư�� �ʱ�ȭ -> ��ġ ���� �ؾ���
    SetStat(100, 60, 10, 1, 5);
    SetResist(0, 0, 0, 0);
    SetReward(50, 10);

    eliteType = EliteType::Normal; // �⺻ ����Ʈ Ÿ�� ���� (Normal)
}

void MusKetShooter::Init()
{
    Enemy::Init();
}

void MusKetShooter::Update(float delta)
{
    Enemy::Update(delta);
}

void MusKetShooter::Render(D2D1_MATRIX_3X2_F cameraMat)
{
    Enemy::Render(cameraMat);
}
