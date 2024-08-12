#pragma once
#include "../D2DEngine/Component.h"
#include "Projectile.h"
#include "Bullet.h"


class MainPineApple;
enum class TurretType {
	Crossbow,
	Musket,
	MineThrower,
	SuperCrossbow,
	SlowWand,
	GrowthPromoter
};

class BulletFactory;
class Turret : public Component
{	
	float shootCooldown = 1.f;           // �Ѿ� �߻� ������ ���� ��ٿ� Ÿ�̸�
	float timeSinceLastShot;       // ���������� �Ѿ��� �߻��� ������ �ð�
protected:
	int level;
	int cost;
	int refund;

	TurretType turretType;
	ProjectileType bulletType;

	float burstRange;
	int damage;
	float fireRate;
	int penetration;
	float bulletSpeed;

	float angle;

public:
	MainPineApple* parentPineApple;
	float prevAngle;
	float currAngle;
	Turret() = default;
	virtual ~Turret() = default;

	void virtual Init() override;
	void virtual Update(float delta) override;

	void Shoot();  // �Ѿ� �߻� �Լ�

	void SetCost(int cost) { this->cost = cost; }
	int GetCost() { return cost; }

	void SetRefund(int refund) { this->refund = refund; }
	int GetRefund() { return refund; }

	void SetBulletType(ProjectileType bulletType) { this->bulletType = bulletType; }
	ProjectileType GetBulletType() { return bulletType; }

	void SetBulletSpeed(float bulletSpeed) { this->bulletSpeed = bulletSpeed; }
	float GetBulletSpeed() { return bulletSpeed; }

	void SetDamage(int damage) { this->damage = damage; }
	int GetDamage() { return damage; }

	void SetFireRate(float fireRate) { this->fireRate = fireRate; }
	float GetFireRate() { return fireRate; }

	void SetPenetration(int penetration) { this->penetration = penetration; }
	int GetPenetration() { return penetration; }

	void SetAngle(float angle) { this->angle = angle; }
	float GetAngle() { return angle; }

};

