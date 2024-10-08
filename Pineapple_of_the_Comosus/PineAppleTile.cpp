#include "PineAppleTile.h"
#include "MainPineApple.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/SpriteRenderer.h"
#include "../D2DEngine/SpriteAnimation.h"
#include "../D2DEngine/SoundManager.h"
#include "DataManager.h"
#include "DynamicData.h"
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
	// 터렛이 활성화되어있지 않다면 설치가능한 타일.
	bool result = turret->isActive == false && pApple->pineAppleLv >= index;
	return result;
}

void PineAppleTile::SetActivateTurret(int typeID)
{
	auto data = DataManager::GetInstance().GetTurretData(typeID);
	//auto spr = turret->GetComponent<SpriteRenderer>();
	auto spr = turret->GetComponent<SpriteAnimation>();
	spr->LoadTexture(data->imagePath);
	spr->LoadAnimationAsset(data->csvPath);

	SoundManager::GetInstance().PlaySoundW(L"NewTurretInstalling_Se");

	auto turretCom = turret->GetComponent<Turret>();
	turretCom->turretType = (TurretType)typeID;
	turretCom->UpdateTurretImage();

	//auto spr = turret->GetComponent<SpriteRenderer>();
	//spr->LoadTexture(path.c_str());
}

void PineAppleTile::Refund()
{
	turret->GetComponent<Turret>()->Refund();
}

void PineAppleTile::ResetTurret()
{
	turret->GetComponent<Turret>()->ResetTurret();
}

