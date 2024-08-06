#pragma once
#include "Turret.h"
class Turret_Mortar : public Turret
{
	public:
	Turret_Mortar() = default;
	~Turret_Mortar() = default;

	void Init() override //8���� ��� �־�� �մϴ� 8�� �ִ��� �׻� Ȯ�����ּ���.
	{
		SetCost(800);
		SetRefund(400);
		SetBulletType(BulletType::Burst);
		SetBulletSpeed(3.0f);
		SetDamage(20);
		SetFireRate(8.0f);
		SetPenetration(5);
		SetAngle(0.0f);
	}
};

