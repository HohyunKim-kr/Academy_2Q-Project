#pragma once
#include "Turret.h"
class Turret_Slow : public Turret
{
	public:
	Turret_Slow() = default;
	~Turret_Slow() = default;

	void Init() override //8���� ��� �־�� �մϴ� 8�� �ִ��� �׻� Ȯ�����ּ���.
	{
		SetCost(600);
		SetRefund(300);
		SetBulletType(BulletType::Burst);
		SetBulletSpeed(0.0f); //�� �κ��� ���ǰ� �ʿ��� �� �մϴ�. ��ȹ�а� ���� ���ּ���.
		SetDamage(0);
		SetFireRate(4.5f);
		SetPenetration(1);
		SetAngle(0.0f);
	}
};

