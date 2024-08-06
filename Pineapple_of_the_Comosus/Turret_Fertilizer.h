#pragma once
#include "Turret.h"
class Turret_Fertilizer : public Turret
{
	public:
	Turret_Fertilizer() = default;
	~Turret_Fertilizer() = default;

	void Init() override //8���� ��� �־�� �մϴ� 8�� �ִ��� �׻� Ȯ�����ּ���.
	{
		SetCost(400);
		SetRefund(0);
		SetBulletType(BulletType::Normal);
		SetBulletSpeed(0.0f);
		SetDamage(0);
		SetFireRate(1.0f);
		SetPenetration(0);
		SetAngle(0.0f);
	}
};

