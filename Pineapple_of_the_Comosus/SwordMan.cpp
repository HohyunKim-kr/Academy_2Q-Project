#include "SwordMan.h"

SwordMan::SwordMan()
{
    // SwordMan Ư�� �ʱ�ȭ
    SetStat(100, 60, 10, 1, 5);
    SetResist(0, 0, 0, 0); 
    SetReward(50, 10); 

    eliteType = EliteType::Normal; // �⺻ ����Ʈ Ÿ�� ���� (Normal)
}

void SwordMan::Init()
{
    Enemy::Init();  
}

void SwordMan::Update(float delta)
{
    Enemy::Update(delta); 
}

void SwordMan::Render(D2D1_MATRIX_3X2_F cameraMat)
{
    Enemy::Render(cameraMat); 
}
