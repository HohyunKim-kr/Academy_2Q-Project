#include "BombCart.h"

//BombCart::BombCart()
//{
//    // BombCart Ư�� �ʱ�ȭ -> ��ġ ���� �ؾ���
//    SetStat(100, 60, 10, 1, 5);
//    SetResist(0, 0, 0, 0);
//    SetReward(50, 10);
//
//    eliteType = EliteType::Normal; // �⺻ ����Ʈ Ÿ�� ���� (Normal)
//}

void BombCart::Init()
{
    Enemy::Init();
}

void BombCart::Update(float delta)
{
    Enemy::Update(delta);
}

void BombCart::Render(D2D1_MATRIX_3X2_F cameraMat)
{
    Enemy::Render(cameraMat);
}
