#pragma once
#include "../D2DEngine/Component.h"
#include "Bullet.h"
#include "DataManager.h"

class MainPineApple;
class TurretData;
class DynamicData;
enum class TurretType {

	Crossbow = 30501,
	Musket = 30511,
	Cannon = 30521,
	SuperCrossbow = 30531,
	SlowWand = 30541,
	GrowthPromoter = 30551

};

class BulletFactory;
class Turret : public Component
{	
	float shootCooldown = 1.f;           // �Ѿ� �߻� ������ ���� ��ٿ� Ÿ�̸�
	float timeSinceLastShot;       // ���������� �Ѿ��� �߻��� ������ �ð�
public:
	TurretType turretType;
	MainPineApple* parentPineApple;
	TurretData* turretData;
	DynamicData* dynamicData;

	float prevAngle;
	float currAngle;
	Turret() = default;
	virtual ~Turret() = default;

	void virtual Init() override;
	void virtual Update(float delta) override;

	void Shoot();  // �Ѿ� �߻� �Լ�



};

