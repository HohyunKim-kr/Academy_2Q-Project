#include "Griffin.h"

//Griffin::Griffin()
//{
//    //// Griffin Ư�� �ʱ�ȭ -> ��ġ ���� �ؾ���
//    //SetStat(100, 60, 10, 1, 5);
//    //SetResist(0, 0, 0, 0);
//    //SetReward(50, 10);
//
//    //eliteType = EliteType::Normal; // �⺻ ����Ʈ Ÿ�� ���� (Normal)
//}

void Griffin::Init()
{
   // Enemy::Init();
}

void Griffin::Update(float delta)
{
    Enemy::Update(delta);
}

void Griffin::Render(D2D1_MATRIX_3X2_F cameraMat)
{
    Enemy::Render(cameraMat);
}
