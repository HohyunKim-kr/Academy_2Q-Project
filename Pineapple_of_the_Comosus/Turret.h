#pragma once
#include "../D2DEngine/Component.h"
#include "Projectile.h"
#include "Bullet.h"
#include "DataManager.h"

class MainPineApple;
class TurretData;
enum class TurretType {
	Crossbow = 30501,
	Musket = 30511,
	MineThrower = 30521,
	SuperCrossbow = 30531,
	SlowWand = 30541,
	GrowthPromoter = 30551
};

class BulletFactory;
class Turret : public Component
{	
	float shootCooldown = 1.f;           // �Ѿ� �߻� ������ ���� ��ٿ� Ÿ�̸�
	float timeSinceLastShot;       // ���������� �Ѿ��� �߻��� ������ �ð�
protected:

	ProjectileType bulletType;

public:
	TurretType turretType;
	MainPineApple* parentPineApple;
	TurretData* turretData;

	float prevAngle;
	float currAngle;
	Turret() = default;
	virtual ~Turret() = default;

	void virtual Init() override;
	void virtual Update(float delta) override;

	void Shoot();  // �Ѿ� �߻� �Լ�



};

