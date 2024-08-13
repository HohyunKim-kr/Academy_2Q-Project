#include "PineAppleTile.h"
#include "MainPineApple.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/SpriteRenderer.h"
#include "DataManager.h"
#include "Turret.h"
#include <string>
void PineAppleTile::Update(float deltaTime)
{

}

void PineAppleTile::IPointerEnter()
{
	pApple->PrintIndex(index);
	isSelected = true;
}

void PineAppleTile::IPointerStay()
{
}

void PineAppleTile::IPointerExit()
{
	isSelected = false;
}

bool PineAppleTile::IsPlaceable()
{
	// �ͷ��� Ȱ��ȭ�Ǿ����� �ʴٸ� ��ġ������ Ÿ��.
	return turret->isActive == false;
}

void PineAppleTile::SetActivateTurret(int typeID)
{
	auto data = DataManager::GetInstance().GetTurretData(typeID);
	auto spr = turret->GetComponent<SpriteRenderer>();
	spr->LoadTexture(data->imagePath);

	auto turretCom = turret->GetComponent<Turret>();
	turretCom->turretType = (TurretType)typeID;

	//auto spr = turret->GetComponent<SpriteRenderer>();
	//spr->LoadTexture(path.c_str());
}

