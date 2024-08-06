#pragma once
#include "Turret.h"
class Turret_CrossBow : public Turret
{
	public:
	Turret_CrossBow() = default;
	~Turret_CrossBow() = default;

	void Init() override //8���� ��� �־�� �մϴ� 8�� �ִ��� �׻� Ȯ�����ּ���.
	{
		SetCost(200);
		SetRefund(100);
		SetBulletType(BulletType::Arrow);
		SetBulletSpeed(10.0f);
		SetDamage(5);
		SetFireRate(1.0f);
		SetPenetration(1);
		SetAngle(0.0f);
	}
};

