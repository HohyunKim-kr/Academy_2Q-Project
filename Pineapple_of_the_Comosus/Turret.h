#pragma once
#include "../D2DEngine/Component.h"
#include "Projectile.h"
#include "Bullet.h"
#include "DataManager.h"

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

	TurretType turretType;
	ProjectileType bulletType;

public:
	MainPineApple* parentPineApple;
	TurretData turretData;

	float prevAngle;
	float currAngle;
	Turret() = default;
	virtual ~Turret() = default;

	void virtual Init() override;
	void virtual Update(float delta) override;

	void Shoot();  // �Ѿ� �߻� �Լ�



};

